#pragma once
#include "mbed.h"
#include "config.h"
#include "ADXL345.h"

// initializes ADXL
void ADXL_init();

// blocking function that collects data from ADXL
void fill_ADXL_buffer();

// convenience function to show what it printed
void print_ADXL_buffer();