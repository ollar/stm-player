#include "i2s_audio.h"
#include "ff.h"
#include "i2s_common.h"
#include "i2s_init.h"
#include "i2s_utils.h"
#include "lvgl/stdlib/lv_string.h"
#include "screens/player.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2s.h"
#include "usart_init.h"
#include <stdlib.h>
#include <string.h>

extern I2S_HandleTypeDef hi2s;
Audio_Data_t audio_data;

FIL fil;
FRESULT fr;
UINT br;
static uint16_t *audio_buffer;
static uint8_t *raw;

extern Player_state_t player_state;

static void fill_audio(FIL *fp, uint16_t *buf, uint16_t frames) {
  UINT br;

  uint8_t bytes_per_frame = audio_data.bytes_per_frame;
  uint8_t bytes_per_channel = bytes_per_frame / audio_data.number_of_channels;
  uint8_t dataformat = audio_data.dataformat;

  if (!player_state.is_playing) {
    lv_memset(buf, 0,
              frames * audio_data.number_of_channels *
                  audio_data.bytes_per_frame);
    return;
  }

  if (f_read(fp, audio_data.raw, frames * bytes_per_frame, &br) != FR_OK)
    br = 0;

  if (br < frames * bytes_per_frame) {
    sd_close_file();
    play_next_track();
  }

  uint8_t *current_byte_pointer = audio_data.raw;
  uint16_t samples_read = br / bytes_per_frame; // 512

  audio_data.bytes_read += br;

  uint32_t peak_left = 0;
  uint32_t peak_right = 0;

  for (uint16_t i = 0; i < frames; i++) {
    int32_t left = 0, right = 0;

    if (i < samples_read) {
      int32_t raw_left = pcm_to_i32(current_byte_pointer, dataformat);
      current_byte_pointer += bytes_per_channel;
      int32_t raw_right = pcm_to_i32(current_byte_pointer, dataformat);
      current_byte_pointer += bytes_per_channel;

      left = (int32_t)(raw_left * player_state.volume);
      right = (int32_t)(raw_right * player_state.volume);

      uint32_t abs_left = (raw_left < 0) ? -raw_left : raw_left;
      uint32_t abs_right = (raw_right < 0) ? -raw_right : raw_right;

      if (abs_left > peak_left)
        peak_left = abs_left;

      if (abs_right > peak_right)
        peak_right = abs_right;
    }

    uint32_t ul = ((uint32_t)left) << 8;
    uint32_t ur = ((uint32_t)right) << 8;

    *buf++ = ul >> 16;    // high half-word
    *buf++ = ul & 0xFFFF; // low half-word
    *buf++ = ur >> 16;
    *buf++ = ur & 0xFFFF;
  }

  audio_data.audio_peak_left = peak_left;
  audio_data.audio_peak_right = peak_right;
}

HAL_StatusTypeDef sd_read_file(char *filename) {

  i2s_deinit();

  fr = f_open(&fil, filename, FA_READ);

  if (fr)
    return (int)fr;

  Wav_Header_t header = {0};
  get_file_header(&fil, &header);

  uint32_t audio_half_frames = get_i2s_buffer_size(&header);

  // TODO: recheck this. rewrite this!
  audio_buffer =
      realloc(audio_buffer, audio_half_frames * 2 * 4 * sizeof(uint16_t));
  raw = realloc(raw, audio_half_frames * header.block_align * sizeof(uint8_t));

  audio_data = (Audio_Data_t){
      .audiofreq = get_i2s_audiofreq(&header),
      .audio_half_frames = audio_half_frames,
      .bytes_per_frame = header.block_align,
      .dataformat = get_i2s_dataformat(&header),
      .number_of_channels = header.number_of_channels,
      .chunk_size = header.chunk_size,
      .byte_rate = header.byte_rate,
      .bytes_read = 0,
      .audio_buffer = audio_buffer,
      .raw = raw,
  };

  i2s_init(&header);

  uint16_t data_offset = wav_find_data_offset(&fil);

  f_lseek(&fil, data_offset);

  fill_audio(&fil, audio_data.audio_buffer, audio_data.audio_half_frames);
  HAL_I2S_Transmit_DMA(&hi2s, audio_data.audio_buffer,
                       audio_data.audio_half_frames * 4);
}

HAL_StatusTypeDef sd_close_file(void) {
  HAL_StatusTypeDef status = HAL_I2S_DMAStop(&hi2s);

  if (audio_data.audio_buffer != NULL) {
    lv_memset(audio_data.audio_buffer, 0,
              audio_data.audio_half_frames * audio_data.number_of_channels *
                  audio_data.bytes_per_frame);
  }

  f_close(&fil);

  return status;
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
  fill_audio(&fil, audio_data.audio_buffer, audio_data.audio_half_frames);
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s) {
  fill_audio(&fil, &audio_data.audio_buffer[audio_data.audio_half_frames * 4],
             audio_data.audio_half_frames);
}
