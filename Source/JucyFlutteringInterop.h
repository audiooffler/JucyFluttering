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
#include "DartApiDL/include/dart_api_dl.c"

// === definitions =============================================================

// for ios, dart/ffi won't be able to access 'extern "C" functions' without those attributes due to compiler optimizations
#if defined(_WIN32)
#define EXTERN_C extern "C" __declspec(dllexport)
#else
#define EXTERN_C extern "C" __attribute__((visibility("default"))) __attribute__((used))
#endif

// === native dart api communication for sending messages to Flutter

EXTERN_C int64_t InitializeDartApi(void *data)
{
  return Dart_InitializeApiDL(data);
}

static int64 DartApiMessagePort = -1;

EXTERN_C void SetDartApiMessagePort(int64 port)
{
  DartApiMessagePort = port;
}

// this will send long integer to dart receiver port as a message
void sendMsgToFlutter(int64 msg)
{
  if (DartApiMessagePort == -1)
    return;
  Dart_CObject obj;
  obj.type = Dart_CObject_kInt64;
  obj.value.as_int64 = msg;
  Dart_PostCObject_DL(DartApiMessagePort, &obj);
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
