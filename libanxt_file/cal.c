/*
    cal.c
    aNXT - a NXt Toolkit
    Libraries and tools for LEGO Mindstorms NXT robots
    Copyright (C) 2008  Janosch Gräf <janosch.graef@gmx.net>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>

#include <anxt/file/cal.h>

/**
 * Sets an BigEndian word
 *  @param buf Buffer to store word in
 *  @param val Value to write as BigEndian
 */
#define BIGENDIAN_SET_WORD(buf,val) { ((uint8_t*)(buf))[0] = (val)/0x100; ((uint8_t*)(buf))[1] = (val)%0x100; }
/**
 * Reads a word as BigEndian
 *  @param buf Buffer where word is in
 *  @return Word
 */
#define BIGENDIAN_GET_WORD(buf)     (((uint16_t)((buf)[0]))*0x100+(buf)[1])

/**
 * Sets an LittleEndian word
 *  @param buf Buffer to store word in
 *  @param val Value to write as LittleEndian
 */
#define LITTLEENDIAN_SET_WORD(buf,val) { ((uint8_t*)(buf))[1] = (val)/0x100; ((uint8_t*)(buf))[0] = (val)%0x100; }
/**
 * Reads a word as LittleEndian
 *  @param buf Buffer where word is in
 *  @return Word
 */
#define LITTLEENDIAN_GET_WORD(buf)     (((uint16_t)((buf)[1]))*0x100+(buf)[0])

/**
 * Encodes calibration data
 *  @param ptr Reference for calibration data
 *  @param min Min. value
 *  @param max Max. value
 *  @note Please free() ptr
 *  @return Size of calibration data
 */
size_t cal_encode(void **ptr,int min,int max) {
  struct cal_data *data = malloc(sizeof(struct cal_data));
  LITTLEENDIAN_SET_WORD(&(data->min),min);
  LITTLEENDIAN_SET_WORD(&(data->max),max);
  *ptr = data;
  return sizeof(struct cal_data);
}

/**
 * Decodes calibration data
 *  @param ptr Calibration data
 *  @param min Reference for min. value
 *  @param max Reference for max. value
 */
void cal_decode(void *ptr,int *min,int *max) {
  struct cal_data *data = (struct cal_data*)ptr;
  if (min!=NULL) *min = LITTLEENDIAN_GET_WORD(&(data->min));
  if (max!=NULL) *max = LITTLEENDIAN_GET_WORD(&(data->max));
}
