#pragma once

#include "mbed.h"
#include "config.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"

void sinLUT_init();
\
// starts timer
void TIM2_start_with_ARR(uint16_t period);

// stops timer, resets it
void TIM2_stop();

void set_frequency(float frequency);

uint32_t * get_sinLUT();