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

// === C++ Symbol export =======================================================

EXTERN_C int increment(int in);

