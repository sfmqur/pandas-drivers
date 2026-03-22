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