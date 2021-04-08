/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "wavegen.h"

int main()
{   
    while (true) {
        
    }
}

void DMA_init() {
    __HAL_RCC_DMA1_CLK_ENABLE();
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}

// Does not start counter by default
void init_timer() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   // enable TIM2 clock
    TIM2->CR2    |= TIM_TRGO_UPDATE;      // set TRGO to update mode
    TIM2->PSC     = 0x0;           // no prescaler
}

// starts timer
void start_timer_with_period(uint32_t period) {
    TIM2->CR1    |= TIM_CR1_UDIS;  // disable updates
    TIM2->ARR     = period;        // set new period
    TIM2->CR1    |= TIM_CR1_CEN;   // enable timer
    TIM2->EGR    |= TIM_EGR_UG;    // force new update
}

// stops timer, resets it
void stop_timer() {
    TIM2->CR1    |= TIM_CR1_UDIS;
    TIM2->ARR     = 0x0;
    TIM2->CR1    &= ~0x1;
    TIM2->EGR    |= TIM_EGR_UG;
}


