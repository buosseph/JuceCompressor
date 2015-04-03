/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginAudioProcessorEditor::PluginAudioProcessorEditor (PluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible (thresholdSlider = new Slider ("Threshold Slider"));
    thresholdSlider->setRange (-20, 0, 0.01);
    thresholdSlider->setSliderStyle (Slider::LinearVertical);
    thresholdSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    thresholdSlider->addListener (this);


    //[UserPreSize]
    // Add any other settings not offered by GUI editor here, else they'll be deleted
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    // Uncomment to apply custom styling from PluginLookAndFeel
//    LookAndFeel::setDefaultLookAndFeel(&pluginLookAndFeel);

    //[/Constructor]
}

PluginAudioProcessorEditor::~PluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    thresholdSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    deleteAllChildren();    // Just in case you miss something (maybe unneeded)
    //[/Destructor]
}

//==============================================================================
void PluginAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff222222));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    thresholdSlider->setBounds (8, 8, 88, 216);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == thresholdSlider)
    {
        //[UserSliderCode_thresholdSlider] -- add your slider handling code here..
        normalizedValue = processor.userParams[processor.threshold].setWithUparam(sliderThatWasMoved->getValue());
        processor.setParameterNotifyingHost(processor.threshold, normalizedValue);
        //[/UserSliderCode_thresholdSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginAudioProcessorEditor::timerCallback() {
    // Set UI values to match any changes made by host automation
    // Timer conflicts cause UI stuttering, this is due to the values not being mapped back
    
    thresholdSlider ->setValue(processor.userParams[processor.threshold].getUparamVal(), dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="PluginAudioProcessor&amp; p" variableInitialisers="AudioProcessorEditor (&amp;p), processor (p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff222222"/>
  <SLIDER name="Threshold Slider" id="1e116366caad33a9" memberName="thresholdSlider"
          virtualName="" explicitFocusOrder="0" pos="8 8 88 216" min="-20"
          max="0" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
