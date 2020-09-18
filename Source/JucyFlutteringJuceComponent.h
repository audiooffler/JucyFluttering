/*
  ==============================================================================

    JucyFlutteringComponent.h
    Created: 18 Sep 2020 11:04:25am
    Author:  Martin Spindler

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class JucyFlutteringJuceComponent  : public juce::Component
{
public:
    JucyFlutteringJuceComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        setSize (600, 400);
    }

    ~JucyFlutteringJuceComponent() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

        g.setFont (juce::Font (16.0f));
        g.setColour (juce::Colours::white);
        g.drawText ("JUCE says hello!", getLocalBounds(), juce::Justification::centred, true);
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JucyFlutteringJuceComponent)
};
