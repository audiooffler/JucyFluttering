/*
  ==============================================================================

    JucyFlutteringJuceApplication.cpp
    Created: 22 Sep 2020
    Author:  audiooffler <sp.martin@gmx.net>
 
  ==============================================================================
*/
#include "JucyFlutteringJuceApplication.h"
#include "JucyFlutteringInterop.h"

// === JUCE App Entry ==========================================================

// for iOS, see IOSAppDelegate, else start juce app
#if !JUCE_IOS
START_JUCE_APPLICATION(JucyFlutteringJuceApplication)
#endif

// === Class JucyFlutteringJuceApplication =====================================

const String JucyFlutteringJuceApplication::getApplicationName()
{
    return "Jucy Fluttering";
}

const String JucyFlutteringJuceApplication::getApplicationVersion()
{
    return "0.0.1";
}

void JucyFlutteringJuceApplication::initialise(const juce::String &)
{
    startTimer(1000);
}

void JucyFlutteringJuceApplication::shutdown()
{
}

void JucyFlutteringJuceApplication::systemRequestedQuit()
{
    quit();
}

// ---- Timer implementation ---------------------------------------------------

// this will send the counter value as an async message to Flutters receiver port
void JucyFlutteringJuceApplication::timerCallback()
{
    i++;
    sendMsgToFlutter(i);
}

// === END of Class JucyFlutteringJuceApplication ==============================
