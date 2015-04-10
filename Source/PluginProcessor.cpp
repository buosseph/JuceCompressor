/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PluginAudioProcessor::PluginAudioProcessor()
{
    userParams[threshold].setMinMax(-20.f, 0.f);
    userParams[threshold].setWithUparam(DEFAULT_THRESHOLD);
    
    userParams[ratio].setMinMax(1.f, 10.f);
    userParams[ratio].setWithUparam(DEFAULT_RATIO);
    
    // Attack and release are in seconds
    userParams[attack].setMinMax(0.f, 0.1f);
    userParams[attack].setWithUparam(DEFAULT_ATTACK);
    userParams[release].setMinMax(0.f, 1.f);
    userParams[release].setWithUparam(DEFAULT_RELEASE);
}

PluginAudioProcessor::~PluginAudioProcessor()
{
}

//==============================================================================
const String PluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int PluginAudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float PluginAudioProcessor::getParameter (int index)
{
    return userParams[index].getVstVal();
}

void PluginAudioProcessor::setParameter (int index, float newValue)
{
    userParams[index].setWithVstVal(newValue);
    switch (index) {
        case threshold:
            setThresh();
            break;
        case ratio:
            setRatio();
            break;
        case attack:
            setAttack();
            break;
        case release:
            setRelease();
            break;
        default:    break;
    }
}

float PluginAudioProcessor::getParameterDefaultValue (int index)
{
    switch (index) {
        case threshold: return DEFAULT_VST_THRESHOLD;
        case ratio:     return DEFAULT_VST_RATIO;
        case attack:    return DEFAULT_VST_ATTACK;
        case release:   return DEFAULT_VST_RELEASE;
        default:        return 0.0f;
    }
}

const String PluginAudioProcessor::getParameterName (int index)
{
    switch (index) {
        case threshold: return "Threshold";
        case ratio:     return "Ratio";
        case attack:    return "Attack";
        case release:   return "Release";
        default:        return String::empty;
    }
}

const String PluginAudioProcessor::getParameterText (int index)
{
    switch (index) {
        case threshold: return String(thresholdDb, 2) + "db";
        case ratio:     return String(userParams[index].getUparamVal(), 2) + ":1";
        case attack:
        case release:
            if (userParams[index].getUparamVal() >= 1.f) {
                return String(userParams[index].getUparamVal(), 2) + "s";
            }
            else {
                return String(userParams[index].getUparamVal() * 1000.f, 2) + "ms";
            }
        default:        return String(getParameter(index), 2);
    }
}

const String PluginAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String PluginAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool PluginAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool PluginAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool PluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double PluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginAudioProcessor::setCurrentProgram (int index)
{
}

const String PluginAudioProcessor::getProgramName (int index)
{
    return String();
}

void PluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void PluginAudioProcessor::setThresh() {
    thresholdDb = userParams[threshold].getUparamVal();
}

void PluginAudioProcessor::setRatio() {
    aRatio = userParams[ratio].getUparamVal();
}

void PluginAudioProcessor::setAttack() {
    attackTime = userParams[attack].getUparamVal();
    gainDymanics->setAttack(attackTime);
}

void PluginAudioProcessor::setRelease() {
    releaseTime = userParams[release].getUparamVal();
    gainDymanics->setRelease(releaseTime);
}

//==============================================================================
void PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    fs = sampleRate;
    gain = 1.f;

    setThresh();
    setRatio();
    attackTime = userParams[attack].getUparamVal();
    releaseTime = userParams[release].getUparamVal();
    
    if (leftLevelDetector == nullptr && rightLevelDetector == nullptr) {
        leftLevelDetector   = new PeakLevelDetector(sampleRate);
        rightLevelDetector  = new PeakLevelDetector(sampleRate);
    }
    else {
        leftLevelDetector   ->setDetector(sampleRate);
        rightLevelDetector  ->setDetector(sampleRate);
    }
    
    if (gainDymanics == nullptr) {
        gainDymanics = new GainDynamics(sampleRate, attackTime, releaseTime);
    }
    else {
        gainDymanics->setDetector(sampleRate);
    }
}

void PluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void PluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    float* leftChannelData  = buffer.getWritePointer (0);
    float* rightChannelData = buffer.getWritePointer (1);
    
    for (int i = 0; i < buffer.getNumSamples(); i++) {
        // Peak detector
        peakOutL = leftLevelDetector->tick(leftChannelData[i]);
        peakOutR = rightLevelDetector->tick(rightChannelData[i]);
        peakSum = (peakOutL + peakOutR) * 0.5f;
        
        // Convert to db
        peakSumDb = dB(peakSum);
        
        // Calculate gain
        if (peakSumDb < thresholdDb) {
            gainDb = 0.f;
        }
        else {
            gainDb = -(peakSumDb - thresholdDb) * (1.f - 1.f/aRatio);
        }
        
        // Gain dynamics (attack and release)
        gainDb = gainDymanics->tick(gainDb);
        
        // Convert to Linear
        gain = dB2mag(gainDb);
        
        // Apply gain
        leftChannelData[i]  *= gain;
        rightChannelData[i] *= gain;
        
//        rightChannelData[i] = gain;           // Debug: Gain Dynamics
    }
}

//==============================================================================
bool PluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginAudioProcessor::createEditor()
{
    return new PluginAudioProcessorEditor (*this);
}

//==============================================================================
void PluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginAudioProcessor();
}
