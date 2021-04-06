#include "wavegen.h"

namespace WaveGen {
    int counter;
    // "private" variables
    namespace {
        AnalogOut output{OUTPUT_PIN};
        Timer _timer;
        Ticker _ticker;
        float _frequency;
        void update_waveform() {
            float t = _timer.elapsed_time().count() / 1e6f; // returned in ns by default, converting to seconds
            float value = arm_sin_f32(t * _frequency) / 2 + 0.5f;
            output = value;
            ++counter;
        }
    };
    void make_sine(float frequency) {
        _frequency = frequency;
        _timer.start();
        counter = 0;
        _ticker.attach(update_waveform, 100us);
    }

    void stop_sine() {
        _ticker.detach();
        _timer.stop();
        _timer.reset();
        output = 0.5;
    }
};