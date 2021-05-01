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
    printf("Initialized sinLUT\n");
    ADXL_init();
    printf("Initialized ADXL!\n");
    set_volume(20);
    printf("Set volume!\n");
    TIM2_start_with_frequency(100);
    printf("\nSuccessfully initialized DMA signal output!\n");
    while (true) {
        if (getchar() == 'd') {
            fill_ADXL_buffer();
            perform_rfft();
            send_rfft_out();
        }
    }
}