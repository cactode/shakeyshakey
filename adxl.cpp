#include "adxl.h"

uint8_t ADXL::read_single(uint8_t reg) {
    char writeVal[]{static_cast<char>(ADXL345_SPI_READ | (reg & 0x3F))};
    char readVal[2];
    _cs = 0;
    wait_ns(5);
    _spi.write(writeVal, 1, readVal, 2);
    _cs = 1;
    return readVal[1];
}

int16_t ADXL::read_y() {
    char writeBuffer[]{
        ADXL345_SPI_READ | ADXL345_MULTI_BYTE | (ADXL345_DATAY0_REG & 0x3F)
    };
    char readBuffer[3];
    _cs = 0;
    wait_ns(5);
    _spi.write(writeBuffer, 1, readBuffer, 3);
    _cs = 1;
    return static_cast<int16_t>(readBuffer[2] << 8 | readBuffer[1]);
}

void ADXL::write(uint8_t reg, uint8_t value) {
    char writeVal[]{static_cast<char>(ADXL345_SPI_WRITE | (reg & 0x3F)), static_cast<char>(value)};
    _cs = 0;
    wait_ns(5);
    _spi.write(writeVal, 2, nullptr, 0);
    _cs = 1;
}

void ADXL::init() {
    write(ADXL345_POWER_CTL_REG,   0b00000000); // turn off 
    write(ADXL345_BW_RATE_REG,     0b00001111); // max data rate
    write(ADXL345_DATA_FORMAT_REG, 0b00000011); // 10bit mode, 16g scale
    write(ADXL345_POWER_CTL_REG,   0b00001000); // turn on
}