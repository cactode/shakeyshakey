#pragma once

#include "mbed.h"
#include "config.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"

// initializes sinLUT
void sinLUT_init();

// starts tone generation with a specific frequency and volume
void start_wavegen(float frequency, uint8_t volume);

// stops tone generation
void stop_wavegen();

// convenience function to make static variable accessable outside of wavegen
uint32_t * get_sinLUT();

// sets volume of amplifier
void set_volume(uint8_t volume);

// initializes amplifier
void MAX_init();