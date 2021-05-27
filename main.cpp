/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "hw_init.h"
#include "wavegen.h"
#include "waveread.h"
#include <algorithm>
#include <array>

constexpr int SWEEP_POINTS{25};
static std::array<float, SWEEP_POINTS> responses; 

float find_peak(const float min_freq, const float max_freq) {
    printf("fmin, fmax = (%f, %f). Responses: ", min_freq, max_freq);
    for (int i = 0; i < SWEEP_POINTS; ++i) {
        float frequency = min_freq
                        + (i 
                        * ((max_freq - min_freq) 
                        / SWEEP_POINTS));
        start_wavegen(frequency, 40);
        ThisThread::sleep_for(100ms);
        fill_accel_buffer();
        // perform_rfft();
        stop_wavegen();
        // responses[i] = get_rfft_at_frequency(frequency) / (frequency * frequency);
        responses[i] = get_peak_reading() / (frequency * frequency);
        printf("%f, ", responses[i]);
    }

    float best_freq = min_freq
                    + (std::distance(responses.begin(), std::max_element(responses.begin(), responses.end()))
                    * ((max_freq - min_freq)
                    / SWEEP_POINTS));
    printf("\b\b. Best frequency: %f\n", best_freq);
    return best_freq;
}

int main() {
    HW_init();
    find_accel_offset();
    float min_freq = 50;
    float max_freq = 1000;
    for (int i = 0; i < 10; i++) {
        printf("On round %i.\n", i);
        float peak = find_peak(min_freq, max_freq);
        float offset = (max_freq - min_freq) / 5;
        min_freq = max(peak - offset, 50.0f);
        max_freq = min(peak + offset, 1000.0f);
    }
    while (1) {
        ThisThread::sleep_for(1000ms);
    }
};