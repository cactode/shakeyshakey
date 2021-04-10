#pragma once
#include "mbed.h"
#include "config.h"
#include "ADXL345.h"

void ADXL_init();

void fill_ADXL_buffer();

void print_ADXL_buffer();