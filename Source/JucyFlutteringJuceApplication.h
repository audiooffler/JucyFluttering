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

// === Class JucyFlutteringJuceApplication =====================================

class JucyFlutteringJuceApplication : public JUCEApplicationBase, public Timer
{
public:
  JucyFlutteringJuceApplication() = default;

  /** Returns the global instance of the application object being run. */
  static JucyFlutteringJuceApplication *JUCE_CALLTYPE getInstance() noexcept
  {
    return dynamic_cast<JucyFlutteringJuceApplication *>(JUCEApplicationBase::getInstance());
  }

  const String getApplicationName() override;
  const String getApplicationVersion() override;
  bool moreThanOneInstanceAllowed() override { return false; }
  void initialise(const juce::String &) override;
  void shutdown() override;
  void anotherInstanceStarted(const String &commandLine) override {}
  void systemRequestedQuit() override;
  void suspended() override {}
  void resumed() override {}
  void unhandledException(const std::exception *, const String &sourceFilename, int lineNumber) override { jassertfalse; }

  // --- Timer implementation -----------------------------------------------

  void timerCallback() override;

private:
  int i = 0;
};
