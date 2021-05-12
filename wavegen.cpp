#include "wavegen.h"

uint32_t sinLUT[SIN_POINTS];
static bool isOn{false};

I2C amplifier{PB_9, PB_8};

// may be turned into a log chirp later, who knows????
void sinLUT_init() {
    for (uint16_t i = 0; i < SIN_POINTS; ++i) {
        float sin = sinf(2 * 3.1415926 * (static_cast<float>(i) / SIN_POINTS));
        sinLUT[i] = static_cast<uint32_t>( (sin / 2.1f + 0.5f) * 4095); // scaled to be a 12-bit unsigned number
    }
    // link table to DMA
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, sinLUT, SIN_POINTS, DAC_ALIGN_12B_R);
}

void TIM2_stop() {
    TIM2->CR1    &= ~TIM_CR1_CEN;                   // disable operation
    DAC1->CR     &= ~DAC_CR_TEN1;                   // disable hardware DMA trigger mode
    TIM2->ARR     = 0x0;                            // blanks out period
    TIM2->EGR    |= TIM_EGR_UG;                     // update shadow registers
    DAC1->DHR12R1 = static_cast<uint32_t>(4096/2);  // set signal to half voltage
    isOn = false;
}

void TIM2_start_with_ARR(uint16_t period) {
    if (isOn) {
        TIM2_stop();
        wait_us(1000);
    }
    DAC1->CR     |= DAC_CR_TEN1;                    // enable hardware DMA trigger mode
    TIM2->ARR     = period;                         // set new period
    TIM2->EGR    |= TIM_EGR_UG;                     // update shadow registers
    TIM2->CR1    |= TIM_CR1_CEN;                    // enable timer
    isOn = true;
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

void set_volume(uint8_t volume) {
    char data = (volume < 64) ? volume : 63;
    amplifier.write(MAX9744_I2CADDR, &data, 1);
}

void MAX_init() {
    set_volume(0);
}

void start_wavegen(float frequency, uint8_t volume) {
    set_volume(volume);
    TIM2_start_with_frequency(frequency);
}

void stop_wavegen() {
    set_volume(0);
    TIM2_stop();
}