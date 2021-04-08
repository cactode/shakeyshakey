#pragma once

#include "mbed.h"
#include "config.h"
#include "arm_math.h"

static uint16_t sinLUT[SIN_POINTS];

void sinLUT_init();
\
// starts timer
void TIM2_start_with_ARR(uint16_t period);

// stops timer, resets it
void TIM2_stop();

void set_frequency(float frequency);