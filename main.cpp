/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "hw_init.h"
#include "wavegen.h"

int main()
{   
    printf("\n\nInitializing hardware...\n");
    HW_init();
    printf("Initialized hardware successfully!\n");
    printf("Initializing sinLUT and DMA...\n");
    sinLUT_init();
    printf("Initalized sinLUT and DMA successfully!\n");
    printf("Snippet of sinLUT:\n");
    for (uint16_t sinValue : sinLUT) {
        printf("%d, " , sinValue);
    }
    while (true) {
        ThisThread::sleep_for(1000ms);
    }
}