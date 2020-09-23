/*
  ==============================================================================

    JucyFlutteringInterop.cpp
    Created: 23 Sep 2020 9:13:30am
    Author:  Martin Spindler

  ==============================================================================
*/

#include "JucyFlutteringInterop.h"

// === C++ Symbol export =======================================================

/* EXTERN_C */ int increment(int in)
{
    DBG("JUCE incrementing "+String(in)+" to "+String(in + 1));
    return in + 1;
}
