/*
 * max31855.h - Driver for MAX31855 Thermocouple Amplifier
 *
 * Copyright (C) 2026 sfmqur <sfmqur@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MAX31855_H
#define MAX31855_H

#include <stdio.h>
#include "pico/stdlib.h"

typedef struct 
{
    uint32_t raw;
    uint8_t status; // open cir 0x1, short to gnd 0x2, short to vcc 0x4, fault bit 0x10
    int16_t internal_temp_raw; // res 0.0625C
    int16_t thermocouple_temp_raw; // res 0.25C
    float internal_temp;
    float thermocouple_temp;
    float cal_1_actual; // use a known temp to calibrate, use desired units in actual
    float cal_2_actual;
    float cal_1_read;
    float cal_2_read;
} max31855_t;

/// @brief initializes the max31855 struct. Ensure that calibration points are pre set.
/// if the points are unknown,  use the same value for actual and read points. 
/// @param result 
void max31855_init(max31855_t *self);

/// @brief processes the 4 bytes of data from the m31855 chip and processes them.
///        the bytes in data are big endian
/// @param data 32 bits of data from max31855 chip. 
/// @param result
void max31855_execute(max31855_t *self, uint8_t *data);

///@brief calibrates the max31855 chip based on calibration points in self.
/// if the points are unknown,  use the same value for actual and read points. 
void max31855_calibrate(max31855_t *self);

/// @brief prints the data from the max31855 chip
/// @param tc 
void max31855_print_data(max31855_t *self);

#endif