/*
  ==============================================================================

    JucyFlutteringMainWindow.h
    Created: 18 Sep 2020 11:10:26am
    Author:  Martin Spindler

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "JucyFlutteringJuceComponent.h"

//==============================================================================
/*
*/
class JucyFlutteringJuceMainWindow  : public juce::DocumentWindow
{
public:
    JucyFlutteringJuceMainWindow (const juce::String& name)
            : DocumentWindow (name, juce::Desktop::getInstance().getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),
                                    juce::DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar (true);
        setContentOwned (new JucyFlutteringJuceComponent(), true);

       #if JUCE_ANDROID || JUCE_IOS
        setFullScreen (true);
       #else
        setResizable (true, false);
        setResizeLimits (300, 250, 10000, 10000);
        centreWithSize (getWidth(), getHeight());
       #endif

        setVisible (true);
    }

    void closeButtonPressed() override
    {
        JUCEApplication::getInstance()->systemRequestedQuit();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JucyFlutteringJuceMainWindow)
};
