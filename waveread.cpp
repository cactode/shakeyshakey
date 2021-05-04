#include "waveread.h"

static uint32_t inputIndex{0};
static int16_t inputBuffer[ADXL_POINTS];
static int readings[]{0,0,0};
static int16_t offset{0};
static float32_t rfftBuffer[ADXL_POINTS];
static float32_t rfftOut[ADXL_POINTS];
static float32_t rfftMag[ADXL_POINTS / 2];

ADXL345 accelerometer{PA_7, PA_6, PA_5, PB_6};

void TIM3_start_with_ARR(uint16_t period) {
    TIM3->ARR     = period;                         // set new period
    TIM3->DIER   |= TIM_IT_UPDATE;                  // enable interrupts
    TIM3->CR1    |= TIM_CR1_CEN;                    // enable timer
}

void TIM3_stop() {
    TIM3->CR1    &= ~TIM_CR1_CEN;                   // disable operation
    TIM3->DIER   &= ~TIM_IT_UPDATE;                 // disable interrupts
    TIM3->ARR     = 0x0;                            // blanks out period
}

// convenience function to make a specific frequency
void TIM3_start_with_frequency(float frequency) {
    TIM3_start_with_ARR(
        static_cast<uint16_t>(
            APB1_FREQ / frequency
        )
    );
}

int16_t ADXL_reading() {
    accelerometer.getOutput(readings);
    return readings[1] - offset;
}

// internal ISR to handle reading from SPI. STM32 HAL is the devil
extern "C" void TIM3_IRQHandler() {
    inputBuffer[inputIndex] = ADXL_reading();
    // self terminate on buffer fill
    if (++inputIndex == ADXL_POINTS) {
        TIM3_stop();
        inputIndex = 0;
    }
}

void ADXL_init() {
    //Go into standby mode to configure the device.
    accelerometer.setPowerControl(0x00);
    //Full resolution, +/-16g, 4mg/LSB.
    accelerometer.setDataFormatControl(0x0B);
    //3.2kHz data rate.
    accelerometer.setDataRate(ADXL345_3200HZ);
    //Measurement mode.
    accelerometer.setPowerControl(0x08);
    fill_ADXL_buffer();
    // calculate offset, accumulate using float as start, implicit conversion to int16_t
    offset = std::accumulate(begin(inputBuffer), end(inputBuffer), 0.0f) / ADXL_POINTS;
}

void fill_ADXL_buffer() {
    TIM3_start_with_frequency(ADXL_FREQ);
    // pause while it finishes up
    ThisThread::sleep_for(ADXL_READ_TIME);
    // ensure it's finished
    while (inputIndex) {
        // stall
    };
}

void print_ADXL_buffer() {
    printf("Input buffer contents:\n");
    for (int i = 0; i < (ADXL_POINTS > 10 ? 10 : ADXL_POINTS); ++i) {
        printf("%i, ", inputBuffer[i]);
    }
    printf("\b\b...\n");
}

void perform_rfft() {
    arm_rfft_fast_instance_f32 rfft;
    arm_rfft_fast_init_f32(&rfft, ADXL_POINTS);
    for (int i = 0; i < ADXL_POINTS; ++i) {
        rfftBuffer[i] = static_cast<float32_t>(inputBuffer[i]);
    }
    arm_rfft_fast_f32(&rfft, rfftBuffer, rfftOut, 0);
    arm_cmplx_mag_f32(rfftOut, rfftMag, ADXL_POINTS / 2);
}

void print_rfft_buffer() {
    printf("rftt buffer contents:\n");
    for (int i = 0; i < (ADXL_POINTS > 10 ? 10 : ADXL_POINTS); ++i) {
        printf("%f, ", rfftBuffer[i]);
    }
    printf("\b\b...\n");
}

void print_rfft_out() {
    printf("Output buffer contents:\n");
    for (int i = 0; i < (ADXL_POINTS > 20 ? 10 : ADXL_POINTS / 2); ++i) {
        printf("%f, ", rfftOut[i]);
    }
    printf("\b\b...\n");
}

void send_rfft_out() {
    for (int i = 0; i < ADXL_POINTS; ++i) {
        printf("%f ", rfftOut[i]);
    }
    printf("\n");
}

void send_rfft_mag() {
    for (int i = 0; i < ADXL_POINTS / 2; ++i) {
        printf("%f ", rfftMag[i]);
    }
    printf("\n");
}