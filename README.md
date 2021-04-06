# Shakey Shakey
A program that uses an accelerometer and a surface transducer to make an object resonate.
My worst idea yet.

## Progress
Naive method of wave generation with a standard MBed OS ticker works horribly.
Will reattempt with direct use of the STM32F446RE DAC.
Saving for later: [DAC Guide](https://www.st.com/resource/en/application_note/cd00259245-audio-and-waveform-generation-using-the-dac-in-stm32-products-stmicroelectronics.pdf)
Page 14 has some relevant stuff, you might also be able to generate chirps with this.