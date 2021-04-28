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
    set_volume(20);
    printf("Set volume!\n");
    TIM2_start_with_frequency(100);
    printf("\nSuccessfully initialized DMA signal output!\n");
    while (true) {
        printf("ADXL reading: %i\n", ADXL_reading());
        fill_ADXL_buffer();
        print_ADXL_buffer();
        ThisThread::sleep_for(1000ms); 
    }
}