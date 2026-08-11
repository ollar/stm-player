#include "ff.h"
#include "i2s_common.h"
#include "stm32f4xx_hal.h"
#include "usart_init.h"
#include <stdint.h>
#include <string.h>

uint8_t get_i2s_dataformat(Wav_Header_t *header) {
  switch (header->bits_per_sample) {
  case 32:
    return I2S_DATAFORMAT_32B;
  case 24:
    return I2S_DATAFORMAT_24B;
  case 16:
    return I2S_DATAFORMAT_16B;
  default:
    return I2S_DATAFORMAT_24B;
  }
}

uint32_t get_i2s_audiofreq(Wav_Header_t *header) {
  switch (header->sample_rate) {
  case 96000:
    return I2S_AUDIOFREQ_96K;
  case 48000:
    return I2S_AUDIOFREQ_48K;
  case 44100:
    return I2S_AUDIOFREQ_44K;
  default:
    return I2S_AUDIOFREQ_48K;
  }
}

uint32_t get_i2s_buffer_size(Wav_Header_t *header) {
  switch (header->sample_rate) {
  case 96000:
    return 1024;
  default:
    return 512;
  }
}

int32_t pcm24_to_i32(const uint8_t *p, uint8_t dataformat) {
  switch (dataformat) {
  case I2S_DATAFORMAT_32B: {
    int32_t s = ((int32_t)p[3] << 24) | ((int32_t)p[2] << 16) |
                ((int32_t)p[1] << 8) | p[0];

    return s >> 8;
  }
  case I2S_DATAFORMAT_16B: {
    int16_t s = (int16_t)((p[1] << 8) | p[0]);
    return ((int32_t)s) << 8;
  }
  case I2S_DATAFORMAT_24B:
  default: {
    int32_t s = ((int32_t)(int8_t)p[2] << 16) | ((int32_t)p[1] << 8) | p[0];
    return s;
  }
  }
}

uint32_t wav_find_data_offset(FIL *fp) {
  char chunkId[4];
  uint32_t chunkSize;
  uint32_t offset = 12; // header is often not less that 44 bytes

  UINT br;

  while (1) {
    f_lseek(fp, offset);
    if (f_read(fp, chunkId, 4, &br) != FR_OK || br != 4)
      return 0;
    if (f_read(fp, &chunkSize, 4, &br) != FR_OK || br != 4)
      return 0;

    if (memcmp(chunkId, "data", 4) == 0) {
      return offset + 8; // move to actual data
    }

    offset += 8 + chunkSize;
    if (offset & 1)
      offset++; // align to even
  }
}

uint8_t header_buffer[256];
Wav_Header_t *get_file_header(FIL *fil) {
  UINT br;

  f_read(fil, header_buffer, 256, &br);

  Wav_Header_t *header = (Wav_Header_t *)&header_buffer;

  hprintf_formatted("header chunk_id: %d\r\n", header->chunk_id);
  hprintf_formatted("header chunk_size: %d\r\n", header->chunk_size);
  hprintf_formatted("header fformat: %.4s\r\n", header->fformat);
  hprintf_formatted("header subchunk1_id: %.4s\r\n", header->subchunk1_id);
  hprintf_formatted("header subchunk1_size: %d\r\n", header->subchunk1_size);
  hprintf_formatted("header audio_format: %d\r\n", header->audio_format);
  hprintf_formatted("header number_of_channels: %d\r\n",
                    header->number_of_channels);
  hprintf_formatted("header sample_rate: %d\r\n", header->sample_rate);
  hprintf_formatted("header byte_rate: %d\r\n", header->byte_rate);
  hprintf_formatted("header block_align: %d\r\n", header->block_align);
  hprintf_formatted("header bits_per_sample: %d\r\n", header->bits_per_sample);
  hprintf_formatted("header subchunk2_id: %.4s\r\n", header->subchunk2_id);
  hprintf_formatted("header subchunk2_size: %d\r\n", header->subchunk2_size);

  return header;
}
