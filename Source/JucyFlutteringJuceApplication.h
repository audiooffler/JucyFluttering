/*
  ==============================================================================

    JucyFlutteringJuceApplication.h
    Created: 22 Sep 2020
    Author:  audiooffler <sp.martin@gmx.net>
 
    This is a very basic headless JUCE application for test purposes.
    It does not instantiate any window but has a background message thread.
    A timer will count seconds and output to debug console.
    The exportet native C++ function "increment" may be called from Flutter UI.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

// === C++ Symbol export =======================================================

extern "C" int increment(int in);

// === Class JucyFlutteringJuceApplication =====================================

class JucyFlutteringJuceApplication    : public JUCEApplication, public Timer
{
public:

    JucyFlutteringJuceApplication() = default;
    const String getApplicationName() override;
    const String getApplicationVersion() override;
    void initialise (const juce::String&) override;
    void shutdown() override;
    void systemRequestedQuit() override;
    
    // --- Timer implementation -----------------------------------------------

    void timerCallback() override;

private:
    int i=0;
};
