#include "adxl.h"

uint8_t ADXL::read_single(uint8_t reg) {
    char writeVal[]{static_cast<char>(ADXL_SPI_READ | (reg & 0x3F))};
    char readVal[2];
    _cs = 0;
    wait_ns(5);
    _spi.write(writeVal, 1, readVal, 2);
    _cs = 1;
    return readVal[1];
}

int16_t ADXL::read_y() {
    char writeBuffer[]{
        ADXL_SPI_READ | ADXL_MULTI_BYTE | (ADXL_DATAY0_REG & 0x3F)
    };
    char readBuffer[3];
    _cs = 0;
    wait_ns(5);
    _spi.write(writeBuffer, 1, readBuffer, 3);
    _cs = 1;
    return static_cast<int16_t>(readBuffer[2] << 8 | readBuffer[1]);
}

void ADXL::write(uint8_t reg, uint8_t value) {
    char writeVal[]{static_cast<char>(ADXL_SPI_WRITE | (reg & 0x3F)), static_cast<char>(value)};
    _cs = 0;
    wait_ns(5);
    _spi.write(writeVal, 2, nullptr, 0);
    _cs = 1;
}

void ADXL::init() {
    write(ADXL_POWER_CTL_REG,   0b00000000); // turn off 
    write(ADXL_BW_RATE_REG,     0b00001111); // max data rate
    write(ADXL_DATA_FORMAT_REG, 0b00000011); // 10bit mode, 16g scale
    write(ADXL_POWER_CTL_REG,   0b00001000); // turn on
}

void ADXL::range(ADXL_RANGE range) {
    write(ADXL_POWER_CTL_REG,   0b00000000); // turn off 
    write(ADXL_DATA_FORMAT_REG, 0b00000011 & static_cast<uint8_t>(range)); // 10bit mode, arbitrary scale
    write(ADXL_POWER_CTL_REG,   0b00001000); // turn on
}