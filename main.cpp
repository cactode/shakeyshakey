/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "hw_init.h"
#include "wavegen.h"
#include "waveread.h"

static float frequency = 100;

int main() {
    HW_init();
    printf("Initialized all hardware!\n");
    while (true) {
        printf("Frequency set to %f\n", frequency);
        start_wavegen(frequency, 20);
        ThisThread::sleep_for(1000ms);
        stop_wavegen();
        ThisThread::sleep_for(1ms);
        frequency += 50;
    }
}
