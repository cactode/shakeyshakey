/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "hw_init.h"
#include "wavegen.h"
#include "waveread.h"

int main() {
    HW_init();
    sinLUT_init();
    TIM2_start_with_frequency(100);
    printf("\nSuccessfully initialized DMA signal output!\n");
    set_volume(63);
    printf("Set volume!\n");
    while (true) {
        ThisThread::sleep_for(1000ms);
        set_volume(1);
        ThisThread::sleep_for(1000ms);
        set_volume(44);
    }
}