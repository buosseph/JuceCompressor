//
//  PeakLevelDetector.cpp
//  BU-P05-Compressor
//
//  Created by Brian Uosseph on 4/3/15.
//
//

#include "PeakLevelDetector.h"

PeakLevelDetector::PeakLevelDetector(float sampleRate) {
    setDetector(sampleRate);
}

PeakLevelDetector::~PeakLevelDetector() {}

float PeakLevelDetector::tick(float inputSample) {
    inputAbs = fabs(inputSample);
    
    if (inputAbs > peakOutput) {
        b0 = b0Attack;
    }
    else {
        b0 = b0Release;
    }
    
    // Simplified filter equation (out = b0 * input + a1 * lastOut)
    peakOutput += b0 * (inputAbs - peakOutput);
    
    return peakOutput;
}

void PeakLevelDetector::setDetector(float sampleRate) {
    fs = sampleRate;
    peakOutput = 0.f;
    
    // set coefficients for leaky integrator
    b0Attack = 1.f;
    a1 = expf(-1 / (releaseTime * fs));
    b0Release = 1.f - a1;
}
