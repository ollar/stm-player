#include "i2s_audio.h"
#include "ff.h"
#include "i2s_common.h"
#include "i2s_init.h"
#include "i2s_utils.h"
#include "stm32f4xx_hal.h"
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

static void fill_audio(FIL *fp, uint16_t *buf, uint16_t frames) {
  UINT br;

  uint8_t bytes_per_frame = audio_data.bytes_per_frame;
  uint8_t bytes_per_channel = bytes_per_frame / audio_data.number_of_channels;
  uint8_t dataformat = audio_data.dataformat;

  if (f_read(fp, audio_data.raw, frames * bytes_per_frame, &br) != FR_OK)
    br = 0;

  uint8_t *current_byte_pointer = audio_data.raw;
  uint16_t samples_read = br / bytes_per_frame; // 512

  for (uint16_t i = 0; i < frames; i++) {
    int32_t left = 0, right = 0;

    if (i < samples_read) {
      left = pcm24_to_i32(current_byte_pointer, dataformat);
      current_byte_pointer += bytes_per_channel;
      right = pcm24_to_i32(current_byte_pointer, dataformat);
      current_byte_pointer += bytes_per_channel;
    }

    uint32_t ul = ((uint32_t)left) << 8;
    uint32_t ur = ((uint32_t)right) << 8;

    *buf++ = ul >> 16;    // high half-word
    *buf++ = ul & 0xFFFF; // low half-word
    *buf++ = ur >> 16;
    *buf++ = ur & 0xFFFF;
  }
}

HAL_StatusTypeDef sd_read_file() {

  i2s_deinit();

  fr = f_open(&fil, "11.WAV", FA_READ);

  hprintf_formatted("file read res %d\r\n", fr);
  if (fr)
    return (int)fr;

  Wav_Header_t *header = {0};
  header = get_file_header(&fil);

  uint32_t audio_half_frames = get_i2s_buffer_size(header);

  audio_buffer =
      realloc(audio_buffer, audio_half_frames * 2 * 4 * sizeof(uint16_t));
  raw = realloc(raw, audio_half_frames * header->block_align * sizeof(uint8_t));

  hprintf_formatted("audio_half_frames %d\r\n", audio_half_frames);

  audio_data = (Audio_Data_t){
      .audiofreq = get_i2s_audiofreq(header),
      .audio_half_frames = audio_half_frames,
      .bytes_per_frame = header->block_align,
      .dataformat = get_i2s_dataformat(header),
      .number_of_channels = header->number_of_channels,
      .audio_buffer = audio_buffer,
      .raw = raw,
  };

  i2s_init(header);

  uint16_t data_offset = wav_find_data_offset(&fil);

  f_lseek(&fil, data_offset);

  fill_audio(&fil, audio_data.audio_buffer, audio_data.audio_half_frames);
  HAL_I2S_Transmit_DMA(&hi2s, audio_data.audio_buffer,
                       audio_data.audio_half_frames * 4);

  hprintf("mehe");

  // free(audio_buffer);
  // free(raw);

  /* Close the file */
  // f_close(&fil);
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
  fill_audio(&fil, audio_data.audio_buffer, audio_data.audio_half_frames);
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s) {
  fill_audio(&fil, &audio_data.audio_buffer[audio_data.audio_half_frames * 4],
             audio_data.audio_half_frames);
}
