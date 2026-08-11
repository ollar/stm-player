#pragma once

#include "ff.h"
#include "i2s_common.h"

uint8_t get_i2s_dataformat(Wav_Header_t *);
uint32_t get_i2s_audiofreq(Wav_Header_t *);
uint32_t get_i2s_buffer_size(Wav_Header_t *);
int32_t pcm24_to_i32(const uint8_t *, uint8_t);
uint32_t wav_find_data_offset(FIL *);
Wav_Header_t *get_file_header(FIL *);
