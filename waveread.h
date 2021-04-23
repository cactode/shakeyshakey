#pragma once
#include "mbed.h"
#include "hw_init.h"
#include "config.h"
#include "ADXL345.h"
#include "arm_math.h"
#include <chrono>
#include <numeric>

// time taken to fill the ADXL buffer
constexpr std::chrono::milliseconds ADXL_READ_TIME{static_cast<int>(1000 * ADXL_POINTS / ADXL_FREQ)};

// initializes ADXL
void ADXL_init();

// blocking function that collects data from ADXL
void fill_ADXL_buffer();

// convenience function to show what it printed
void print_ADXL_buffer();

// convenience function to get ADXL reading
int16_t ADXL_reading();