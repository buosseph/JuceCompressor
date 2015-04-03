//
//  UParam.h
//  mu45-LD-P01-Volume-V2
//
//  Created by Luke Dahl on 2/2/15.
//
//

#ifndef __mu45_LD_P01_Volume_V2__UParam__
#define __mu45_LD_P01_Volume_V2__UParam__

#include <stdio.h>

#endif /* defined(__mu45_LD_P01_Volume_V2__UParam__) */

// This is a simple class for keeping track of two different versions of
// a user parameter. One version, the vstValue is is always between
// 0.0 and 1.0, which VST expects all values to be.
// The other is the actual value of the user parameter in other
// units, such as dB.
//
// This class performs a linear mapping from vstValue to uParamVal
// and vice versa. It needs to know the minimum and maximum values
// of the user parameter to do so.

class UParam
{
public:
    // three different constructors
    UParam(){minVal = 0; maxVal = 1.0; vstVal = 0.0; uParamVal = 0.0;}
    UParam(float min, float max){setMinMax(min,max); vstVal = 0; calcUparam();}
    UParam(float min, float max, float sVal){setMinMax(min,max);
        setWithVstVal(sVal);}

    // call this to set the min and max values of the userParameter
    void setMinMax(float min, float max){
        minVal = min;
        maxVal = max;
    }
    
    // set the value from a vst value
    float setWithVstVal(float val){
        vstVal = val;
        calcUparam();
        return uParamVal;
    }
    
    // set the value with the uParam value
    float setWithUparam(float val){
        uParamVal = val;
        calcVst();
        return vstVal;
    }
    
    // get the current vst value
    float getVstVal(){return vstVal;}
    
    // get the current userParam value
    float getUparamVal(){return uParamVal;}
    
private:
    float vstVal;       // the vst value is always 0.0 to 1.0
    float uParamVal;    // the actual user parameter value
    float minVal;       // the minimum uParam value
    float maxVal;       // the maximum uParam value
    
    // calculate the uParam val from the vst value
    void calcUparam(){
        uParamVal = minVal + (maxVal - minVal)*vstVal;
    }
    
    // calculate that vst value from the uParam val
    void calcVst(){
        vstVal = (uParamVal - minVal)/(maxVal - minVal);
    }
};
