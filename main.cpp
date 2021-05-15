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
    find_accel_offset();
    while (true) {
        float frequency = 100;
        getchar();
        while (frequency < 1000) {
            start_wavegen(frequency, 30);
            ThisThread::sleep_for(50ms);
            fill_accel_buffer();
            perform_rfft();
            stop_wavegen();
            printf("%f %f ", frequency, get_rfft_at_frequency(frequency));
            ThisThread::sleep_for(1ms);
            frequency += 10;
        }
        printf("\n");
    ThisThread::sleep_for(1000ms);
    };
}
