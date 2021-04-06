#pragma once

#include "mbed.h"
#include "config.h"
#include "arm_math.h"
#include <chrono>

// quasi-singleton design pattern since we don't want more than one of these floating around
namespace WaveGen {
    extern int counter;
    void make_sine(float frequency);
    void stop_sine();
};