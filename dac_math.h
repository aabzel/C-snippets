#ifndef DAC_MATH_H
#define DAC_MATH_H

#include "rx_stdbool.h"

#include "float_utils.h"
#include <stdint.h>

#define PI (3.14159265f)

/*TODO:  move to tx_utils*/
float_t calc_pwm_sample (
    uint64_t curTimeUs,
    float_t inFrequency,
    float_t inPhaseMs,
    float_t inVoltageAmplitude,
    float_t inYOffset,
    float_t inDutyCycle);

float_t calc_fence_sample (uint64_t inTimeUs, float_t inFrequency, float_t inPhaseMs, float_t inVoltageAmplitude, float_t inOffset);
float_t calc_saw_sample (uint64_t inTimeUs, float_t inFrequency, float_t inPhaseMs, float_t inVoltageAmplitude, float_t inOffset);
float_t calc_sin_sample (uint64_t inTimeUs, float_t inFrequency, float_t inPhaseMs, float_t inVoltageAmplitude, float_t inOffset); /*TODO:  move to tx_utils*/
float_t signnum (float_t value); /*MOVE to rx_utils*/
uint16_t voltage2sample (float_t inVoltage, float_t inOapGain, uint16_t maxSampleVal, float_t dacVrefV);

#endif /* DAC_MATH_H */
