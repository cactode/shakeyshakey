#include "waveread.h"
#include <chrono>

static int16_t inputBuffer[ADXL_POINTS];

ADXL345 accelerometer{PA_7, PA_6, PA_5, PB_6};

void ADXL_init() {
    //Go into standby mode to configure the device.
    accelerometer.setPowerControl(0x00);
    //Full resolution, +/-16g, 4mg/LSB.
    accelerometer.setDataFormatControl(0x0B);
    //3.2kHz data rate.
    accelerometer.setDataRate(ADXL345_3200HZ);
    //Measurement mode.
    accelerometer.setPowerControl(0x08);
}

void fill_ADXL_buffer() {
    int readings[]{0,0,0};
    for (int i = 0; i < ADXL_POINTS; ++i) {
        accelerometer.getOutput(readings);
        inputBuffer[i] = (int16_t)readings[0];
        wait_us(static_cast<uint16_t>(1e6 / ADXL_FREQ));
    }
}

void print_ADXL_buffer() {
    int readings[3] = {0,0,0};
    for (int i = 0; i < ADXL_POINTS; ++i) {
        wait_us(static_cast<uint16_t>(1e6 / ADXL_FREQ));
        accelerometer.getOutput(readings);
        printf("%i, ", (int16_t) readings[0]);
    }
}