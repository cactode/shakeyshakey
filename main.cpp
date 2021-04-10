/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "hw_init.h"
#include "wavegen.h"
#include "waveread.h"

int main() {
    DigitalOut led{LED1};
    ADXL_init();
    printf("\n\nInitialized ADXL!\nSnippets of inputBuffer:\n");
    while (true) {
        led = !led;
        // fill_ADXL_buffer();
        led = !led;
        print_ADXL_buffer();
        ThisThread::sleep_for(1000ms);
    }
}

// int main()
// {   
//     DigitalOut led{LED1};
//     printf("\n\nInitializing hardware...\n");
//     HW_init();
//     printf("Initialized hardware successfully!\n");
//     printf("Initializing sinLUT and DMA...\n");
//     sinLUT_init();
//     printf("Initalized sinLUT and DMA successfully!\n");
//     printf("Snippet of sinLUT:\n");
//     for (int i = 0; i < SIN_POINTS / 10; ++i) {
//         printf("%d, " , get_sinLUT()[i]);
//     }
//     while (true) {
//         ThisThread::sleep_for(1000ms);
//         led = !led;
//         printf("Starting DMA sin stream\n");
//         TIM2_start_with_frequency(100);
//         ThisThread::sleep_for(1000ms);
//         printf("Stoppping DMA sin stream\n");
//         TIM2_stop();
//     }
// }