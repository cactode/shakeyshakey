/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "wavegen.h"

int main()
{   
    while (true) {
        printf("Output on\n");
        WaveGen::make_sine(10 * 6.283);
        ThisThread::sleep_for(1000ms);
        printf("Output off, activated %d times\n", WaveGen::counter);
        WaveGen::stop_sine();
        ThisThread::sleep_for(1000ms);
    }
}
