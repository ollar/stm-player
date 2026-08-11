/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --stride 1 --align 1 --font
 * UbuntuMono-Regular.ttf --symbols
 * ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789
 * .,!?-*+/=$%^@#&()АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя
 * --format lvgl -o ubuntu_mono.c
 ******************************************************************************/

#ifdef __has_include
#if __has_include("lvgl.h")
#ifndef LV_LVGL_H_INCLUDE_SIMPLE
#define LV_LVGL_H_INCLUDE_SIMPLE
#endif
#endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef UBUNTU_MONO
#define UBUNTU_MONO 1
#endif

#if UBUNTU_MONO

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x55, 0x54, 0xf0,

    /* U+0023 "#" */
    0x24, 0x4b, 0xf9, 0x66, 0xc9, 0x3f, 0xa4, 0x48, 0x90,

    /* U+0024 "$" */
    0x23, 0xe1, 0xc, 0x30, 0xc1, 0x8, 0x7c, 0x42, 0x0,

    /* U+0025 "%" */
    0x63, 0x2a, 0x74, 0xc7, 0x2, 0x8a, 0x95, 0x4b, 0x88,

    /* U+0026 "&" */
    0x30, 0x91, 0x22, 0xc7, 0xe, 0xa7, 0x46, 0x8c, 0xec,

    /* U+0028 "(" */
    0x13, 0x64, 0xc8, 0x88, 0x88, 0xc4, 0x63, 0x10,

    /* U+0029 ")" */
    0x8c, 0x62, 0x31, 0x11, 0x11, 0x32, 0x6c, 0x80,

    /* U+002A "*" */
    0x25, 0x7e, 0xc5, 0x28,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0x6c, 0xa8,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x20, 0x86, 0x10, 0x43, 0xc, 0x20, 0x86, 0x10, 0x43, 0x0,

    /* U+0030 "0" */
    0x79, 0x28, 0x6d, 0xb6, 0x18, 0x61, 0x49, 0xc0,

    /* U+0031 "1" */
    0x23, 0x28, 0x42, 0x10, 0x84, 0x27, 0xc0,

    /* U+0032 "2" */
    0xf2, 0x20, 0x82, 0x10, 0xc6, 0x10, 0xc3, 0xf0,

    /* U+0033 "3" */
    0xf2, 0x20, 0x82, 0x70, 0x30, 0x41, 0xf, 0xe0,

    /* U+0034 "4" */
    0xc, 0x38, 0x51, 0x24, 0x58, 0xbf, 0x82, 0x4, 0x8,

    /* U+0035 "5" */
    0x7d, 0x4, 0x10, 0x78, 0x30, 0x41, 0xf, 0xe0,

    /* U+0036 "6" */
    0x1d, 0x84, 0x3e, 0x8e, 0x18, 0x61, 0x49, 0xe0,

    /* U+0037 "7" */
    0xfc, 0x30, 0x86, 0x10, 0xc2, 0x8, 0x21, 0x80,

    /* U+0038 "8" */
    0x7a, 0x38, 0x61, 0x79, 0x68, 0x61, 0x85, 0xe0,

    /* U+0039 "9" */
    0x7b, 0x28, 0x61, 0xc5, 0xf0, 0x42, 0x1b, 0x80,

    /* U+003D "=" */
    0xfe, 0x0, 0x7, 0xf0,

    /* U+003F "?" */
    0xf0, 0x42, 0x33, 0x31, 0x0, 0x63, 0x0,

    /* U+0040 "@" */
    0x3c, 0xc9, 0xc, 0xfb, 0x34, 0x68, 0xd1, 0xb3, 0x3d, 0x3, 0x1, 0xc0,

    /* U+0041 "A" */
    0x18, 0x18, 0x24, 0x24, 0x24, 0x66, 0x7e, 0x42, 0x42, 0xc3,

    /* U+0042 "B" */
    0xfa, 0x38, 0x63, 0xfa, 0x38, 0x61, 0x8f, 0xe0,

    /* U+0043 "C" */
    0x3d, 0xc, 0x20, 0x82, 0x8, 0x20, 0x40, 0xf0,

    /* U+0044 "D" */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0x61, 0x8b, 0xc0,

    /* U+0045 "E" */
    0xfa, 0x8, 0x20, 0xfa, 0x8, 0x20, 0x83, 0xf0,

    /* U+0046 "F" */
    0xfc, 0x21, 0xf, 0xc2, 0x10, 0x84, 0x0,

    /* U+0047 "G" */
    0x3d, 0x1c, 0x20, 0x82, 0x18, 0x71, 0x44, 0xf0,

    /* U+0048 "H" */
    0x86, 0x18, 0x61, 0xfe, 0x18, 0x61, 0x86, 0x10,

    /* U+0049 "I" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0x27, 0xc0,

    /* U+004A "J" */
    0x3c, 0x10, 0x41, 0x4, 0x10, 0x41, 0xd, 0xe0,

    /* U+004B "K" */
    0x8d, 0x12, 0x45, 0xe, 0x1c, 0x24, 0x4c, 0x8d, 0x8,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x83, 0xf0,

    /* U+004D "M" */
    0xc7, 0x8f, 0xbd, 0x5a, 0xb2, 0x60, 0xc1, 0x83, 0x4,

    /* U+004E "N" */
    0x87, 0x1e, 0x69, 0xb6, 0x59, 0x63, 0x8e, 0x10,

    /* U+004F "O" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44, 0x70,

    /* U+0050 "P" */
    0xfa, 0x38, 0x61, 0x8f, 0xe8, 0x20, 0x82, 0x0,

    /* U+0051 "Q" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xc6, 0xf8, 0xe0, 0xc0, 0xe0,

    /* U+0052 "R" */
    0xf9, 0x1a, 0x14, 0x28, 0xdf, 0x26, 0x44, 0x85, 0x8,

    /* U+0053 "S" */
    0x7e, 0x8, 0x20, 0x70, 0x60, 0x41, 0x7, 0xe0,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10, 0x20,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0xcd, 0xe0,

    /* U+0056 "V" */
    0xc3, 0x42, 0x42, 0x42, 0x66, 0x24, 0x24, 0x3c, 0x18, 0x18,

    /* U+0057 "W" */
    0x83, 0x6, 0xc, 0x19, 0x35, 0x6a, 0xf7, 0xc7, 0x8c,

    /* U+0058 "X" */
    0x42, 0x66, 0x24, 0x3c, 0x18, 0x18, 0x2c, 0x24, 0x66, 0x42,

    /* U+0059 "Y" */
    0xc3, 0x8d, 0x13, 0x62, 0x82, 0x4, 0x8, 0x10, 0x20,

    /* U+005A "Z" */
    0xfc, 0x30, 0x84, 0x30, 0x86, 0x10, 0xc3, 0xf0,

    /* U+005E "^" */
    0x30, 0xc4, 0x92, 0x86, 0x10,

    /* U+0061 "a" */
    0x78, 0x30, 0x5f, 0xc6, 0x18, 0x5f,

    /* U+0062 "b" */
    0x82, 0x8, 0x20, 0xf2, 0x28, 0x61, 0x86, 0x18, 0xbc,

    /* U+0063 "c" */
    0x3d, 0x8, 0x20, 0x82, 0x4, 0xf,

    /* U+0064 "d" */
    0x4, 0x10, 0x41, 0x3d, 0x18, 0x61, 0x86, 0x14, 0x4f,

    /* U+0065 "e" */
    0x39, 0x38, 0x7f, 0x82, 0x4, 0xf,

    /* U+0066 "f" */
    0x1e, 0x40, 0x87, 0xe2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80,

    /* U+0067 "g" */
    0x3d, 0x18, 0x61, 0x86, 0x14, 0x5f, 0x4, 0x3f, 0x80,

    /* U+0068 "h" */
    0x82, 0x8, 0x20, 0xfa, 0x38, 0x61, 0x86, 0x18, 0x61,

    /* U+0069 "i" */
    0x61, 0x80, 0x38, 0x20, 0x82, 0x8, 0x20, 0x81, 0xc0,

    /* U+006A "j" */
    0x18, 0xc0, 0xf0, 0x84, 0x21, 0x8, 0x42, 0x10, 0xf8,

    /* U+006B "k" */
    0x82, 0x8, 0x20, 0x8a, 0x6b, 0x30, 0xe2, 0x48, 0xa3,

    /* U+006C "l" */
    0xe0, 0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x81, 0xc0,

    /* U+006D "m" */
    0xed, 0x26, 0x4c, 0x99, 0x30, 0x60, 0xc1,

    /* U+006E "n" */
    0xfa, 0x38, 0x61, 0x86, 0x18, 0x61,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0xbc, 0x82, 0x8, 0x0,

    /* U+0071 "q" */
    0x3d, 0x18, 0x61, 0x86, 0x14, 0x4f, 0x4, 0x10, 0x40,

    /* U+0072 "r" */
    0xfc, 0x21, 0x8, 0x42, 0x10,

    /* U+0073 "s" */
    0x7e, 0x8, 0x1c, 0x18, 0x10, 0x7e,

    /* U+0074 "t" */
    0x20, 0x8f, 0xc8, 0x20, 0x82, 0x8, 0x20, 0x70,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x1c, 0x5f,

    /* U+0076 "v" */
    0x42, 0x42, 0x66, 0x24, 0x24, 0x3c, 0x18, 0x18,

    /* U+0077 "w" */
    0xc3, 0xc3, 0x5a, 0x5a, 0x5a, 0x66, 0x66, 0x66,

    /* U+0078 "x" */
    0x42, 0x24, 0x3c, 0x18, 0x18, 0x24, 0x66, 0x42,

    /* U+0079 "y" */
    0x87, 0x1c, 0xd2, 0x49, 0xa3, 0x8c, 0x10, 0x8c, 0x0,

    /* U+007A "z" */
    0xfc, 0x31, 0x8c, 0x21, 0x8c, 0x3f,

    /* U+0401 "Ё" */
    0x49, 0x20, 0x3f, 0x82, 0x8, 0x3e, 0x82, 0x8, 0x20, 0xfc,

    /* U+0410 "А" */
    0x18, 0x18, 0x24, 0x24, 0x24, 0x66, 0x7e, 0x42, 0x42, 0xc3,

    /* U+0411 "Б" */
    0xfa, 0x8, 0x20, 0xfa, 0x38, 0x61, 0x8f, 0xe0,

    /* U+0412 "В" */
    0xfa, 0x38, 0x63, 0xfa, 0x38, 0x61, 0x8f, 0xe0,

    /* U+0413 "Г" */
    0x3e, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10, 0x21, 0xf0,

    /* U+0414 "Д" */
    0x3e, 0x44, 0x89, 0x12, 0x24, 0x48, 0xb1, 0x43, 0xfe, 0xc, 0x18, 0x20,

    /* U+0415 "Е" */
    0xfa, 0x8, 0x20, 0xfa, 0x8, 0x20, 0x83, 0xf0,

    /* U+0416 "Ж" */
    0x93, 0xad, 0x53, 0xe3, 0x8f, 0x15, 0x2a, 0x93, 0x24,

    /* U+0417 "З" */
    0xf8, 0x8, 0x10, 0x67, 0x80, 0x80, 0x81, 0x87, 0xf8,

    /* U+0418 "И" */
    0x86, 0x39, 0xe5, 0xb6, 0x9e, 0x71, 0xc6, 0x10,

    /* U+0419 "Й" */
    0x49, 0xe0, 0x21, 0x8e, 0x79, 0x6d, 0xa7, 0x9c, 0x71, 0x84,

    /* U+041A "К" */
    0x8d, 0x12, 0x45, 0xe, 0x1c, 0x24, 0x4c, 0x8d, 0x8,

    /* U+041B "Л" */
    0x3e, 0x44, 0x89, 0x12, 0x24, 0x48, 0xa1, 0x43, 0x4,

    /* U+041C "М" */
    0xc7, 0x8f, 0xbd, 0x5a, 0xb2, 0x60, 0xc1, 0x83, 0x4,

    /* U+041D "Н" */
    0x86, 0x18, 0x61, 0xfe, 0x18, 0x61, 0x86, 0x10,

    /* U+041E "О" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44, 0x70,

    /* U+041F "П" */
    0xfe, 0x18, 0x61, 0x86, 0x18, 0x61, 0x86, 0x10,

    /* U+0420 "Р" */
    0xfa, 0x38, 0x61, 0x8f, 0xe8, 0x20, 0x82, 0x0,

    /* U+0421 "С" */
    0x3d, 0xc, 0x20, 0x82, 0x8, 0x20, 0x40, 0xf0,

    /* U+0422 "Т" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10, 0x20,

    /* U+0423 "У" */
    0xc3, 0x42, 0x62, 0x26, 0x34, 0x14, 0x18, 0x8, 0x10, 0x60,

    /* U+0424 "Ф" */
    0x10, 0x71, 0xf4, 0x99, 0x32, 0x64, 0xc9, 0x7c, 0x70, 0x40,

    /* U+0425 "Х" */
    0x42, 0x66, 0x24, 0x3c, 0x18, 0x18, 0x2c, 0x24, 0x66, 0x42,

    /* U+0426 "Ц" */
    0x85, 0xa, 0x14, 0x28, 0x50, 0xa1, 0x42, 0x85, 0xfc, 0x8, 0x10, 0x20,

    /* U+0427 "Ч" */
    0x86, 0x18, 0x61, 0xc5, 0xf0, 0x41, 0x4, 0x10,

    /* U+0428 "Ш" */
    0x83, 0x6, 0xc, 0x19, 0x32, 0x64, 0xc9, 0x93, 0xfc,

    /* U+0429 "Щ" */
    0x85, 0xa, 0x14, 0x29, 0x52, 0xa5, 0x4a, 0x95, 0xfc, 0x8, 0x10, 0x20,

    /* U+042A "Ъ" */
    0xe0, 0x40, 0x81, 0xe2, 0x64, 0x48, 0x91, 0x26, 0x78,

    /* U+042B "Ы" */
    0x83, 0x6, 0xf, 0x99, 0xb1, 0x62, 0xc5, 0x9b, 0xe4,

    /* U+042C "Ь" */
    0x82, 0x8, 0x3c, 0x8e, 0x18, 0x61, 0x8f, 0xe0,

    /* U+042D "Э" */
    0xf0, 0x20, 0x41, 0x7c, 0x10, 0x43, 0xb, 0xc0,

    /* U+042E "Ю" */
    0x9d, 0x6a, 0x8d, 0x1e, 0x34, 0x68, 0xd1, 0x95, 0x38,

    /* U+042F "Я" */
    0x7f, 0x18, 0x61, 0xc5, 0xf6, 0x51, 0xc6, 0x10,

    /* U+0430 "а" */
    0x78, 0x30, 0x5f, 0xc6, 0x18, 0x5f,

    /* U+0431 "б" */
    0x1d, 0xc4, 0x20, 0xfb, 0x38, 0x61, 0x86, 0x14, 0x9e,

    /* U+0432 "в" */
    0xfa, 0x18, 0x7e, 0x86, 0x18, 0xfe,

    /* U+0433 "г" */
    0xfc, 0x21, 0x8, 0x42, 0x10,

    /* U+0434 "д" */
    0x3c, 0x48, 0x91, 0x22, 0x4c, 0x91, 0x7f, 0x83, 0x4,

    /* U+0435 "е" */
    0x39, 0x38, 0x7f, 0x82, 0x4, 0xf,

    /* U+0436 "ж" */
    0xd6, 0xa9, 0xf1, 0xc3, 0x8a, 0xb5, 0xc9,

    /* U+0437 "з" */
    0xf0, 0x42, 0xe0, 0x84, 0x3e,

    /* U+0438 "и" */
    0x86, 0x39, 0xed, 0xa7, 0x1c, 0x61,

    /* U+0439 "й" */
    0x48, 0xe0, 0x21, 0x8e, 0x7b, 0x69, 0xc7, 0x18, 0x40,

    /* U+043A "к" */
    0x8a, 0x6b, 0x30, 0xe2, 0x48, 0xa3,

    /* U+043B "л" */
    0x3c, 0x92, 0x49, 0x25, 0x94, 0x61,

    /* U+043C "м" */
    0xc7, 0x8f, 0x3d, 0x5a, 0xb7, 0x60, 0xc1,

    /* U+043D "н" */
    0x86, 0x18, 0x7f, 0x86, 0x18, 0x61,

    /* U+043E "о" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+043F "п" */
    0xfe, 0x18, 0x61, 0x86, 0x18, 0x61,

    /* U+0440 "р" */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0xbc, 0x82, 0x8, 0x0,

    /* U+0441 "с" */
    0x3d, 0x8, 0x20, 0x82, 0x4, 0xf,

    /* U+0442 "т" */
    0xfc, 0x41, 0x4, 0x10, 0x41, 0x4,

    /* U+0443 "у" */
    0x87, 0x1c, 0xd2, 0x49, 0xa3, 0x8c, 0x10, 0x8c, 0x0,

    /* U+0444 "ф" */
    0x10, 0x20, 0x40, 0x87, 0xca, 0xa4, 0xc9, 0x93, 0x25, 0x53, 0xe1, 0x2, 0x4,
    0x0,

    /* U+0445 "х" */
    0x42, 0x24, 0x3c, 0x18, 0x18, 0x24, 0x66, 0x42,

    /* U+0446 "ц" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x7f, 0x4, 0x10,

    /* U+0447 "ч" */
    0x86, 0x18, 0x61, 0x7c, 0x10, 0x41,

    /* U+0448 "ш" */
    0x83, 0x6, 0x4c, 0x99, 0x32, 0x64, 0xff,

    /* U+0449 "щ" */
    0x85, 0xa, 0x54, 0xa9, 0x52, 0xa5, 0x7f, 0x2, 0x4,

    /* U+044A "ъ" */
    0xc0, 0x81, 0x3, 0xe4, 0x68, 0x50, 0xbe,

    /* U+044B "ы" */
    0x86, 0x18, 0x79, 0x96, 0x59, 0x79,

    /* U+044C "ь" */
    0x82, 0x8, 0x3e, 0x8e, 0x18, 0x7e,

    /* U+044D "э" */
    0x78, 0x8, 0x19, 0xf0, 0x60, 0xc3, 0x7c,

    /* U+044E "ю" */
    0x9d, 0x46, 0x8f, 0x1a, 0x34, 0x69, 0xce,

    /* U+044F "я" */
    0x7f, 0x18, 0x61, 0x7d, 0x1c, 0x61,

    /* U+0451 "ё" */
    0x28, 0xa3, 0x93, 0x87, 0xf8, 0x20, 0x40, 0xe0};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0,
     .adv_w = 0,
     .box_w = 0,
     .box_h = 0,
     .ofs_x = 0,
     .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0,
     .adv_w = 128,
     .box_w = 1,
     .box_h = 1,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 1,
     .adv_w = 128,
     .box_w = 2,
     .box_h = 10,
     .ofs_x = 3,
     .ofs_y = 0},
    {.bitmap_index = 4,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 13,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 13,
     .ofs_x = 1,
     .ofs_y = -2},
    {.bitmap_index = 22,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 31,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 40,
     .adv_w = 128,
     .box_w = 4,
     .box_h = 15,
     .ofs_x = 2,
     .ofs_y = -3},
    {.bitmap_index = 48,
     .adv_w = 128,
     .box_w = 4,
     .box_h = 15,
     .ofs_x = 2,
     .ofs_y = -3},
    {.bitmap_index = 56,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 6,
     .ofs_x = 1,
     .ofs_y = 4},
    {.bitmap_index = 60,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 7,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 67,
     .adv_w = 128,
     .box_w = 3,
     .box_h = 5,
     .ofs_x = 2,
     .ofs_y = -3},
    {.bitmap_index = 69,
     .adv_w = 128,
     .box_w = 4,
     .box_h = 1,
     .ofs_x = 2,
     .ofs_y = 4},
    {.bitmap_index = 70,
     .adv_w = 128,
     .box_w = 2,
     .box_h = 2,
     .ofs_x = 3,
     .ofs_y = 0},
    {.bitmap_index = 71,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 14,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 82,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 90,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 10,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 97,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 105,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 113,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 122,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 130,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 138,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 146,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 154,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 162,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 4,
     .ofs_x = 1,
     .ofs_y = 2},
    {.bitmap_index = 166,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 10,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 173,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 13,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 185,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 195,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 203,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 211,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 219,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 227,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 234,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 242,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 250,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 257,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 265,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 274,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 282,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 291,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 299,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 308,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 316,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 13,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 328,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 337,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 345,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 354,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 362,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 372,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 381,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 391,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 400,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 408,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 6,
     .ofs_x = 1,
     .ofs_y = 4},
    {.bitmap_index = 413,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 419,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 428,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 434,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 443,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 449,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 459,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 468,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 477,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 486,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 14,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 495,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 504,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 513,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 520,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 526,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 533,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 542,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 551,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 8,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 556,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 562,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 570,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 576,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 8,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 584,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 8,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 592,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 8,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 600,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 609,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 615,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 13,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 625,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 635,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 643,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 651,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 660,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 13,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 672,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 680,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 689,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 698,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 706,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 13,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 716,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 725,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 734,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 743,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 751,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 760,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 768,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 776,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 784,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 793,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 803,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 813,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 823,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 13,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 835,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 843,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 852,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 13,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 864,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 873,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 882,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 890,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 898,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 907,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 915,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 921,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 930,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 936,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 8,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 941,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = -2},
    {.bitmap_index = 950,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 956,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 8,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 963,
     .adv_w = 128,
     .box_w = 5,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 968,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 974,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 983,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 989,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 995,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1002,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1008,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1015,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1021,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 1030,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1036,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1042,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 1051,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 15,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 1065,
     .adv_w = 128,
     .box_w = 8,
     .box_h = 8,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 1073,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = -2},
    {.bitmap_index = 1081,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1087,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1094,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = -2},
    {.bitmap_index = 1103,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1110,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1116,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1122,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1129,
     .adv_w = 128,
     .box_w = 7,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1136,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 8,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 1142,
     .adv_w = 128,
     .box_w = 6,
     .box_h = 10,
     .ofs_x = 1,
     .ofs_y = 0}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0,  1,  0,  2,  3,  4,  5,  0,  6,  7,  8,  9, 10, 11, 12,
    13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 0,  0,  24};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {.range_start = 32,
     .range_length = 30,
     .glyph_id_start = 1,
     .unicode_list = NULL,
     .glyph_id_ofs_list = glyph_id_ofs_list_0,
     .list_length = 30,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL},
    {.range_start = 63,
     .range_length = 28,
     .glyph_id_start = 26,
     .unicode_list = NULL,
     .glyph_id_ofs_list = NULL,
     .list_length = 0,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY},
    {.range_start = 94,
     .range_length = 1,
     .glyph_id_start = 54,
     .unicode_list = NULL,
     .glyph_id_ofs_list = NULL,
     .list_length = 0,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY},
    {.range_start = 97,
     .range_length = 26,
     .glyph_id_start = 55,
     .unicode_list = NULL,
     .glyph_id_ofs_list = NULL,
     .list_length = 0,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY},
    {.range_start = 1025,
     .range_length = 1,
     .glyph_id_start = 81,
     .unicode_list = NULL,
     .glyph_id_ofs_list = NULL,
     .list_length = 0,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY},
    {.range_start = 1040,
     .range_length = 64,
     .glyph_id_start = 82,
     .unicode_list = NULL,
     .glyph_id_ofs_list = NULL,
     .list_length = 0,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY},
    {.range_start = 1105,
     .range_length = 1,
     .glyph_id_start = 146,
     .unicode_list = NULL,
     .glyph_id_ofs_list = NULL,
     .list_length = 0,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY}};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 7,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ubuntu_mono = {
#else
lv_font_t ubuntu_mono = {
#endif
    .get_glyph_dsc =
        lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap =
        lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 16, /*The maximum line height required by the font*/
    .base_line = 3,    /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 0,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc, /*The custom font data. Will be accessed by
                         `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /*#if UBUNTU_MONO*/
