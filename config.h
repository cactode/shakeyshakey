#pragma once
#include "mbed.h"

constexpr PinName OUTPUT_PIN{PA_4};

constexpr uint32_t SIN_POINTS{128};

constexpr uint16_t ADXL_POINTS{10};

constexpr float ADXL_FREQ{10};

constexpr float APB1_FREQ{90e6};

constexpr uint8_t MAX9744_I2CADDR{0x4B << 1};