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
    set_volume(40);
    printf("Set volume!\n");
    printf("\nSuccessfully initialized DMA signal output!\n");
    while (true) {
        if (getchar() == 'd') {
            TIM2_start_with_frequency(100);
            ThisThread::sleep_for(100ms);
            fill_ADXL_buffer();
            send_adxl_buffer();
            perform_rfft();
            send_rfft_mag();
            TIM2_stop();
        } else {
            ThisThread::sleep_for(100ms);
            fill_ADXL_buffer();
            send_adxl_buffer();
            perform_rfft();
            send_rfft_mag();
        }
    }
}