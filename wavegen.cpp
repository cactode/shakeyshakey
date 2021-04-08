#include "wavegen.h"

static DAC_HandleTypeDef hdac1;

void sinLUT_init() {
    for (int i = 0; i < SIN_POINTS; ++i) {
        float sin = arm_cos_f32(1.0f / i);
        SIN_POINTS[i] = static_cast<uint16_t>( (sin / 2 + 0.5) * 4096) // scaled to be a 12-bit unsigned number
    }
    // link table to DMA
    HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, sinLUT, SIN_POINTS, DAC_ALIGN_12B_R);

}

// starts timer
void TIM2_start_with_ARR(uint16_t period) {
    TIM2->CR1    |= TIM_CR1_UDIS;  // disable updates
    TIM2->ARR     = period;        // set new period
    TIM2->CR1    |= TIM_CR1_CEN;   // enable timer
    TIM2->EGR    |= TIM_EGR_UG;    // force new update
}

// stops timer, resets it
void TIM2_stop() {
    TIM2->CR1    |= TIM_CR1_UDIS;  // disables updates
    TIM2->ARR     = 0x0;           // blanks out period
    TIM2->CR1    &= ~0x1;          // disable operation
    TIM2->EGR    |= TIM_EGR_UG;    // force new update
}

void set_frequency(float frequency) {
    TIM2_start_with_ARR(
        static_cast<uint16_t>(
            APB1_FREQ / (frequency * SIN_POINTS)
        )
    );
}