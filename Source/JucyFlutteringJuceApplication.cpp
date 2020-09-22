/*
  ==============================================================================

    JucyFlutteringJuceApplication.cpp
    Created: 22 Sep 2020
    Author:  audiooffler <sp.martin@gmx.net>
 
  ==============================================================================
*/

#include "JucyFlutteringJuceApplication.h"

// === C++ Symbol export =======================================================

/* EXTERN_C */ int increment(int in)
{
    DBG("JUCE incrementing "+String(in)+" to "+String(in + 1));
    return in + 1;
}



// === JUCE App Entry ==========================================================

// for iOS, see IOSAppDelegate, else start juce app
#if !JUCE_IOS
START_JUCE_APPLICATION (JucyFlutteringJuceApplication)
#endif



// === Class JucyFlutteringJuceApplication =====================================

const String JucyFlutteringJuceApplication::getApplicationName()
{
    return "JucyFluttering";
}

const String JucyFlutteringJuceApplication::getApplicationVersion()
{
    return "0.0.1";
}

void JucyFlutteringJuceApplication::initialise (const juce::String&)
{
    startTimer(1000);
}

void JucyFlutteringJuceApplication::systemRequestedQuit()
{
    quit();
}

void JucyFlutteringJuceApplication::shutdown()
{
    
}

// ---- Timer implementation ---------------------------------------------------

void JucyFlutteringJuceApplication::timerCallback()
{
    DBG("timer "+String(i));
    i++;
}

// === END of Class JucyFlutteringJuceApplication ==============================
