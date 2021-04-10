#pragma once

#include "mbed.h"
#include "config.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"

// initializes sinLUT
void sinLUT_init();

// starts timer
void TIM2_start_with_ARR(uint16_t period);

// stops timer, resets it
void TIM2_stop();

void TIM2_start_with_frequency(float frequency);

// convenience function to make static variable accessable outside of wavegen
uint32_t * get_sinLUT();