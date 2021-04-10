#include "wavegen.h"

uint32_t sinLUT[SIN_POINTS];

void sinLUT_init() {
    for (int i = 0; i < SIN_POINTS; ++i) {
        float sin = sinf(2 * 3.1415926 * (static_cast<float>(i) / SIN_POINTS));
        sinLUT[i] = static_cast<uint32_t>( (sin / 2.1 + 0.5) * 4095); // scaled to be a 12-bit unsigned number
    }
    // link table to DMA
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, sinLUT, SIN_POINTS, DAC_ALIGN_12B_R);
}

void TIM2_start_with_ARR(uint16_t period) {
    DAC1->CR     |= DAC_CR_TEN1;                    // enable hardware DMA trigger mode
    TIM2->ARR     = period;                         // set new period
    TIM2->CR1    |= TIM_CR1_CEN;                    // enable timer
}

void TIM2_stop() {
    TIM2->CR1    &= ~TIM_CR1_CEN;                   // disable operation
    TIM2->ARR     = 0x0;                            // blanks out period
    DAC1->CR     &= ~DAC_CR_TEN1;                   // disable hardware DMA trigger mode
    DAC1->DHR12R1 = static_cast<uint32_t>(4096/2);  // set signal to half voltage
}

// convenience function to make a specific frequency
void TIM2_start_with_frequency(float frequency) {
    TIM2_start_with_ARR(
        static_cast<uint16_t>(
            APB1_FREQ / (frequency * SIN_POINTS)
        )
    );
}

uint32_t * get_sinLUT() {
    return sinLUT;
}