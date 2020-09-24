/*
  ==============================================================================

    JucyFlutteringInterop.h
    Created: 22 Sep 2020
    Author:  audiooffler <sp.martin@gmx.net>

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "JucyFlutteringJuceApplication.h"

// === definitions =============================================================

// for ios, dart/ffi won't be able to access 'extern "C" functions' without those attributes due to compiler optimizations
#define EXTERN_C extern "C" __attribute__((visibility("default"))) __attribute__((used))

// call this once from flutter, when initializing the flutter app! this enables to use callbacks from juce message loop to flutter (callbacks allowed only in same thread as flutter)
EXTERN_C void startJuceApplicationAndEventLoop()
{
#if !JUCE_IOS

#endif
  //const MessageManagerLock mmLock;

  //MessageManager* mm = MessageManager::getInstanceWithoutCreating();
  //mm->setCurrentThreadAsMessageThread();
  DBG("called startJuceApplicationAndEventLoop");
}

// === Helper typedefs for callback functions ==================================

typedef void (*void_functionPtr)();
typedef int32_t (*int_functionPtr)();
typedef void (*void_functionPtr_int)(int32_t);
typedef int32_t (*int_functionPtr_int)(int32_t);
typedef void (*int_functionPtr_Utf8StringPtr)(char *);

// === Helper functions ========================================================

// copy a juce String to a null-terminated UTF8 char* pointer, using 'malloc()' and 'strcpy()',
// so don't forget, the caller must call 'free()' on the returned utf8 pointer
const char *copyStringToUTF8(String juceString)
{
  return strcpy(((char *)(malloc(juceString.getNumBytesAsUTF8()))), juceString.toRawUTF8());
}

// === C++ symbol export funtions ==============================================

EXTERN_C int calcIncrement(int in)
{
  DBG("JUCE incrementing " + String(in) + " to " + String(in + 1));
  return in + 1;
}

// returns an utf8 (char pointer) string, to be freed by the caller
EXTERN_C const char *getAppName()
{
  return copyStringToUTF8(JucyFlutteringJuceApplication::getInstance()->getApplicationName());
}

/*
EXTERN_C int32_t juceFoo( int32_t bar, int32_t (*callback)(void*, int32_t) )
{
    return callback(nullptr, bar);
}
 */

void_functionPtr dartDecrementCallback = nullptr;
EXTERN_C void registerDartDecrementCallback(void_functionPtr dartNativeCallbackFunction)
{
  dartDecrementCallback = dartNativeCallbackFunction;
}