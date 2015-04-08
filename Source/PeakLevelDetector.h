//
//  PeakLevelDetector.h
//  BU-P05-Compressor
//
//  Created by Brian Uosseph on 4/3/15.
//
//

#ifndef BU_P05_Compressor_PeakLevelDetector_h
#define BU_P05_Compressor_PeakLevelDetector_h

#include <math.h>

class PeakLevelDetector {
public:
    PeakLevelDetector(float sampleRate);
    ~PeakLevelDetector();
    
    float tick(float inputSample);
    void setDetector(float sampleRate);
    
private:
    float fs, inputAbs, peakOutput;
    float b0Attack, b0Release, b0, a1;
    float releaseTime = 0.100f;     // seconds
};

#endif
