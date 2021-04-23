#pragma once
#include "mbed.h"

// DAC output pin
constexpr PinName OUTPUT_PIN{PA_4};

// points to use in sin interpolation
constexpr uint32_t SIN_POINTS{256};

// points to collect from adxl
constexpr uint16_t ADXL_POINTS{2048};

// frequency to acquire samples at
constexpr float ADXL_FREQ{3000};

// frequency of clock for TIM2-TIM5 block
constexpr float APB1_FREQ{90e6};

// I2C read address for amplifier
constexpr uint8_t MAX9744_I2CADDR{0x4B << 1};