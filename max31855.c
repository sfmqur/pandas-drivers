#include <stdio.h>
#include "pico/stdlib.h"
#include "max31855.h"

static float cal_slope = 1;
static float cal_offset = 0;


void max31855_init(max31855_t *self) {
    self->raw = 0;
    self->status = 0;
    self->internal_temp_raw = 0;
    self->thermocouple_temp_raw = 0;
    self->internal_temp = 0;
    self->thermocouple_temp = 0;

    max31855_calibrate(self);
}

void max31855_execute(max31855_t *self, uint8_t *data) {
    uint32_t raw  = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]);
    self->raw = raw;
    self->status = (raw & 0x7) | ((raw & 0x10000) >> 12);
    self->internal_temp_raw = (raw & 0xFFF0) >> 4;
    self->thermocouple_temp_raw = (raw & 0xFFFC0000) >> 16;

    if (self->internal_temp_raw & 0x0800){ // 12 bit, sign extend to 16
        self->internal_temp_raw |= 0xF800;
    }
    if (self->thermocouple_temp_raw & 0x2000){ // 14 bit, sign extend to 16
        self->thermocouple_temp_raw   |= 0xC000;
    }

    self->internal_temp = (self->internal_temp_raw * 0.0625) * cal_slope + cal_offset;
    self->thermocouple_temp = (self->thermocouple_temp_raw * 0.25) * cal_slope + cal_offset;
}

void max31855_calibrate(max31855_t *self) {
    cal_slope = (self->cal_2_actual - self->cal_1_actual) / (self->cal_2_read - self->cal_1_read);
    cal_offset = self->cal_1_actual - (self->cal_1_read * cal_slope);
}

void max31855_print_data(max31855_t* tc) {
    printf("Raw: 0x%X\n", tc->raw);
    printf("Status: 0x%X\n", tc->status);
    printf("Internal Temp Raw: %d\n", tc->internal_temp_raw);
    printf("Thermocouple Temp Raw: %d\n", tc->thermocouple_temp_raw);
    printf("Internal Temp: %f\n", tc->internal_temp);
    printf("Thermocouple Temp: %f\n\n", tc->thermocouple_temp);
}
