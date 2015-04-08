//
//  LeakyIntegrator.cpp
//  BU-P05-Compressor
//
//  Created by Brian Uosseph on 4/7/15.
//
//

#include "LeakyIntegrator.h"

GainDynamics::GainDynamics(float sampleRate, float attackTime, float releaseTime) {
    attackTime = attackTime;
    releaseTime = releaseTime;
    setDetector(sampleRate);
}

GainDynamics::~GainDynamics() {}

// gain is linear
float GainDynamics::tick(float inputGain) {
    if (inputGain > outputGain) {
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

void GainDynamics::setAttack(float attackTime) {
    attackTime = attackTime;
    a1Attack = expf(-1 / (attackTime * fs));
    b0Attack = 1.f - a1Attack;
}

void GainDynamics::setRelease(float releaseTime) {
    releaseTime = releaseTime;
    a1Release = expf(-1 / (releaseTime * fs));
    b0Release = 1.f - a1Release;
}
