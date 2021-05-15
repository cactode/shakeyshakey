#pragma once
#include "mbed.h"
#include "config.h"
#include "adxl.h"
#include "arm_math.h"
#include <chrono>
#include <numeric>

// time taken to fill the ADXL buffer
constexpr std::chrono::milliseconds ADXL_READ_TIME{static_cast<int>(1000 * ADXL_POINTS / ADXL_FREQ)};

constexpr float FREQ_BIN_WIDTH{ADXL_FREQ / (2 * ADXL_POINTS)};

// initializes ADXL
void ADXL_init();

// sets range of accelerometer
void set_range(uint8_t range);

// find gravitational offset
void find_accel_offset();

// blocking function that collects data from ADXL
void fill_accel_buffer();

// convenience function to show what it printed
void print_accel_buffer();

// convenience function to see RFFT buffer?
void print_rfft_buffer();

// perform an rfft
void perform_rfft();

// get a specific rfft value
float get_rfft_at_frequency(float frequency);

// convenience functino to see RFFT output?
void print_rfft_out();

// sends adxl buffer in a more machine readable format
void send_adxl_buffer();

// sends rfft in a more machine readable format
void send_rfft_out();

// sends rfft complex magnitude in a more machine readable format
void send_rfft_mag();

// convenience function to get ADXL reading
int16_t ADXL_reading();