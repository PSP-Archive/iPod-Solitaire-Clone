/* gameplaySP
 *
 * Copyright (C) 2006 Exophase <exophase@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef COMMON_H
#define COMMON_H

#define ror(dest, value, shift)                                               \
  dest = ((value) >> shift) | ((value) << (32 - shift))                       \

// Huge thanks to pollux for the heads up on using native file I/O
// functions on PSP for vastly improved memstick performance.

  #define fastcall

  #include <pspkernel.h>
  #include <pspdebug.h>
  #include <pspctrl.h>
  #include <pspgu.h>

  #define function_cc

  #define convert_palette(value)                                              \
    value = ((value & 0x7E00) << 1) | ((value & 0x03E0) << 1) |               \
     (value & 0x1F)                                                           \

  #define psp_file_open_read  PSP_O_RDONLY
  #define psp_file_open_write (PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC)

  #define file_open(filename_tag, filename, mode)                             \
    s32 filename_tag = sceIoOpen(filename, psp_file_open_##mode, 0777)        \

  #define file_check_valid(filename_tag)                                      \
    (filename_tag >= 0)                                                       \

  #define file_close(filename_tag)                                            \
    sceIoClose(filename_tag)                                                  \

  #define file_read(filename_tag, buffer, size)                               \
    sceIoRead(filename_tag, buffer, size)                                     \

  #define file_write(filename_tag, buffer, size)                              \
    sceIoWrite(filename_tag, buffer, size)                                    \

  #define file_seek(filename_tag, offset, type)                               \
    sceIoLseek(filename_tag, offset, PSP_##type)                              \

typedef u32 fixed16_16;

#define float_to_fp16_16(value)                                               \
  (fixed16_16)((value) * 65536.0)                                             \

#define fp16_16_to_float(value)                                               \
  (float)((value) / 65536.0)                                                  \

#define u32_to_fp16_16(value)                                                 \
  ((value) << 16)                                                             \

#define fp16_16_to_u32(value)                                                 \
  ((value) >> 16)                                                             \

#define fp16_16_fractional_part(value)                                        \
  ((value) & 0xFFFF)                                                          \

#define fixed_div(numerator, denominator, bits)                               \
  (((numerator * (1 << bits)) + (denominator / 2)) / denominator)             \

#define address8(base, offset)                                                \
  *((u8 *)((u8 *)base + (offset)))                                            \

#define address16(base, offset)                                               \
  *((u16 *)((u8 *)base + (offset)))                                           \

#define address32(base, offset)                                               \
  *((u32 *)((u8 *)base + (offset)))                                           \

  #define printf pspDebugScreenPrintf

#endif

