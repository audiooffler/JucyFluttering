/*
  ==============================================================================

    JucyFlutteringInterop.h
    Created: 22 Sep 2020
    Author:  audiooffler <sp.martin@gmx.net>

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define EXTERN_C extern "C" __attribute__((visibility("default"))) __attribute__((used))

// copy a juce String to a null-terminated UTF8 char* pointer, using 'malloc()' and 'strcpy()',
// so don't forget, the caller must call 'free()' on the returned utf8 pointer
const char* copyStringToUTF8(String juceString)
{
    return strcpy(((char *) (malloc(juceString.getNumBytesAsUTF8()))), juceString.toRawUTF8());
}

// === C++ Symbol export =======================================================

EXTERN_C int increment(int in)
{
    DBG("JUCE incrementing "+String(in)+" to "+String(in + 1));
    return in + 1;
}

// returns an utf8 (char pointer) string, to be freed by the caller
EXTERN_C const char* getAppName()
{
    return copyStringToUTF8(JUCEApplication::getInstance()->getApplicationName());
}

