#pragma once
#include <stdint.h>

// Python:
// - chunk_id (4s) = bytes 0-3
// - chunk_size (I) = bytes 4-7
// - fformat (4s) = bytes 8-11
// - subchunk1_id (4s) = bytes 12-15
// - subchunk1_size (I) = bytes 16-19
// - audio_format (h) = bytes 20-21
// - number_of_channels (h) = bytes 22-23
// - sample_rate (I) = bytes 24-27
// - byte_rate (I) = bytes 28-31
// - block_align (h) = bytes 32-33
// - bits_per_sample (h) = bytes 34-35
// - subchunk2_id (4s) = bytes 36-39
// - subchunk2_size (I) = bytes 40-43

/*
header chunk_id: 1179011410
header chunk_size: 53284038
header fformat: WAVE
header subchunk1_id: fmt
header subchunk1_size: 40
header audio_format: 65534
header number_of_channels: 2
header sample_rate: 48000
header byte_rate: 288000
header block_align: 6
header bits_per_sample: 24
header subchunk2_id:
header subchunk2_size: 3
 */

typedef struct {
  uint32_t chunk_id;
  uint32_t chunk_size;
  char fformat[4];
  char subchunk1_id[4];
  uint32_t subchunk1_size;
  uint16_t audio_format;
  uint16_t number_of_channels;
  uint32_t sample_rate;
  uint32_t byte_rate;
  uint16_t block_align;
  uint16_t bits_per_sample;
  char subchunk2_id[4];
  uint32_t subchunk2_size;
} Wav_Header_t;

typedef struct {
  uint32_t audiofreq;
  uint32_t audio_half_frames;
  uint16_t bytes_per_frame;
  uint8_t dataformat;
  uint8_t number_of_channels;
  uint32_t chunk_size;
  uint32_t byte_rate;
  uint32_t bytes_read;
  uint16_t *audio_buffer;
  uint8_t *raw;
} Audio_Data_t;
