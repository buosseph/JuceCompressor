//
//  GainDynamics.h
//  BU-P05-Compressor
//
//  Created by Brian Uosseph on 4/7/15.
//
//

#ifndef __BU_P05_Compressor__LeakyIntegrator__
#define __BU_P05_Compressor__LeakyIntegrator__

#include <math.h>

class GainDynamics {
public:
    GainDynamics(float sampleRate, float attackTime, float releaseTime);
    ~GainDynamics();
    
    float tick(float inputSample);
    void setDetector(float sampleRate);
    void setAttack(float attackTime);
    void setRelease(float releaseTime);
    
private:
    float fs, outputGain;
    double b0Attack, b0Release, b0;
    float attackTime, releaseTime;     // in seconds
};

#endif /* defined(__BU_P05_Compressor__LeakyIntegrator__) */
