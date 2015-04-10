//
//  LeakyIntegrator.cpp
//  BU-P05-Compressor
//
//  Created by Brian Uosseph on 4/7/15.
//
//

#include "GainDynamics.h"

// Times are in seconds (e.g. 100ms = 0.1f, 1.2s = 1.2f)
GainDynamics::GainDynamics(float sampleRate, float newAttackTime, float newReleaseTime) {
    attackTime = newAttackTime;
    releaseTime = newReleaseTime;
    setDetector(sampleRate);
}

GainDynamics::~GainDynamics() {}

float GainDynamics::tick(float inputGain) {
    if (inputGain < outputGain) {   // Isn't this suppose to be (input > lastOutput)?
        b0 = b0Attack;
    }
    else {
        b0 = b0Release;
    }
    
    // Simplified filter equation (out = b0 * input + a1 * lastOut)
    outputGain += b0 * (inputGain - outputGain);
    
    return outputGain;
}

void GainDynamics::setDetector(float sampleRate) {
    fs = sampleRate;
    outputGain = 0.f;
    setAttack(attackTime);
    setRelease(releaseTime);
}

void GainDynamics::setAttack(float newAttackTime) {
    attackTime = newAttackTime;
    b0Attack = 1. - expf(-1. / (attackTime * fs));;
}

void GainDynamics::setRelease(float newReleaseTime) {
    releaseTime = newReleaseTime;
    b0Release = 1. - expf(-1. / (releaseTime * fs));;
}
