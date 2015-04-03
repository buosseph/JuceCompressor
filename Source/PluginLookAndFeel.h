/*
  ==============================================================================

    PluginLookAndFeel.h
    Created: 4 Feb 2015 2:16:44pm
    Author:  Brian Uosseph

  ==============================================================================
*/

#ifndef PLUGINLOOKANDFEEL_H_INCLUDED
#define PLUGINLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class PluginLookAndFeel: public LookAndFeel_V2
{
public:
    PluginLookAndFeel();
    virtual ~PluginLookAndFeel();

    /* Slider styling */
    virtual void drawLinearSlider (Graphics& g,
                           int x, int y,
                           int width, int height,
                           float sliderPos,
                           float minSliderPos,
                           float maxSliderPos,
                           const Slider::SliderStyle style,
                           Slider& slider);

    virtual void drawRotarySlider (Graphics& g,
                           int x, int y,
                           int width, int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           Slider& slider);
private:
    Path rotaryPath;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginLookAndFeel)
};

#endif  // PLUGINLOOKANDFEEL_H_INCLUDED
