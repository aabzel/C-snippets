#include "dac_math.h"

float_t signnum (float_t value) {
    float_t outVal = 0.0f;
    if (0.0f < value) {
        outVal = 1.0f;
    }
    if (value < 0.0f) {
        outVal = 0.0f;
    }
    return outVal;
}

float_t calc_pwm_sample (
    uint64_t curTimeUs,
    float_t inFrequency,
    float_t inPhaseMs,
    float_t inVoltageAmplitude,
    float_t inYOffset,
    float_t inDutyCycle) {
    float_t lineVal = 0.0f;
    float_t sawVal = 0.0f;

    float_t amplitude = 0.0f;
    float_t amplitudeScaled = 0.0f;
    float_t currentTimeMs = ((float_t) curTimeUs) / 1000.0f;
    lineVal = ((currentTimeMs + inPhaseMs) / 1000.0f) * inFrequency; /*tune frequency*/
    sawVal = fmodf (lineVal, 1.0f); /*tune DutyCycle*/
    amplitude = inVoltageAmplitude * signnum ((((100.0f - inDutyCycle)) / 100.0f) - sawVal); /*tune DutyCycle*/
    /*tune amplitude*/
    amplitudeScaled = (inVoltageAmplitude * amplitude) + inYOffset;

    return amplitudeScaled;
}

float_t calc_sin_sample (uint64_t inTimeUs, float_t inFrequency, float_t inPhaseMs, float_t inVoltageAmplitude, float_t inOffset) {
    float_t lineVal = 0.0f;
    float_t argument = 0.0f;
    float_t amplitude = 0.0f;
    float_t amplitudeScaled = 0.0f;
    float_t currentTimeMs = ((float_t) inTimeUs) / 1000.0f;
    lineVal = ((currentTimeMs + inPhaseMs) / 1000.0f) * inFrequency; /*tune frequency*/
    argument = 2.0f * PI * lineVal;
    amplitude = (float_t) sin ((double_t) argument); /*tune DutyCycle*/
    /*tune amplitude*/
    amplitudeScaled = (inVoltageAmplitude * amplitude) + inOffset;
    /*outDacSample = cacl_sample (amplitudeScaled, BIG_OAP_GAIN);*/

    return amplitudeScaled;
}

float_t calc_saw_sample (uint64_t inTimeUs, float_t inFrequency, float_t inPhaseMs, float_t inVoltageAmplitude, float_t inOffset) {
    float_t argument = 0.0f;
    float_t amplitude = 0.0f;
    float_t amplitudeScaled = 0.0f;
    float_t currentTimeMs = ((float_t) inTimeUs) / 1000.0f;
    argument = ((currentTimeMs + inPhaseMs) / 1000.0f) * inFrequency; /*tune frequency*/

    amplitude = (float_t) inVoltageAmplitude * fmod ((double_t) argument, (double_t) 1.0f);
    /*tune amplitude*/
    amplitudeScaled = amplitude + inOffset;

    return amplitudeScaled;
}

float_t calc_fence_sample (uint64_t inTimeUs, float_t inFrequency, float_t inPhaseMs, float_t inVoltageAmplitude, float_t inOffset) {
    float_t argument = 0.0f;
    float_t amplitude = 0.0f;
    float_t amplitudeScaled = 0.0f;
    float_t currentTimeMs = ((float_t) inTimeUs) / 1000.0f;
    argument = ((currentTimeMs + inPhaseMs) / 1000.0f) * inFrequency; /*tune frequency*/

    amplitude = 1.0f - fabs (fmod ((double_t) argument * 2.0f, 2.0f) - 1.0f);
    /*tune amplitude*/
    amplitudeScaled = inVoltageAmplitude * amplitude + inOffset;

    return amplitudeScaled;
}

uint16_t voltage2sample (float_t inVoltage, float_t inOapGain, uint16_t maxSampleVal, float_t dacVrefV) {
    uint16_t outSample = 0U;
    float_t maxPosVolgateForGain = inOapGain * dacVrefV;
    float_t codePerVoltsForGain = ((float_t) (maxSampleVal + 1.0f)) / maxPosVolgateForGain;
    if (maxSampleVal < (inVoltage * codePerVoltsForGain)) {
        outSample = maxSampleVal - 1U;
    } else {
        if ((inVoltage * codePerVoltsForGain) < 0.0f) {
            outSample = 0x0000U;
        } else {
            /*TODO: fix MISRA 2012 Rule 10.8: invalid cast from "float" to "uint16_t"      */
            outSample = (uint16_t) (inVoltage * codePerVoltsForGain);
        }
    }
    return outSample;
}
