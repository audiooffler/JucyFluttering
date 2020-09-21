#include <JuceHeader.h>
#include "JucyFlutteringJuceMainWindow.h"
#include "JucyFlutteringJuceComponent.h"

extern "C" void hello_world()
{
    DBG("Hello World from JUCE library.");
}

class JucyFlutteringJuceApplication    : public juce::JUCEApplication, public Timer
{
public:
    //==============================================================================
    JucyFlutteringJuceApplication() = default;

    const juce::String getApplicationName() override       { return "JucyFluttering"; }
    const juce::String getApplicationVersion() override    { return "0.0.1"; }

    void initialise (const juce::String&) override
    {
        //jucyFlutteringJuceMainWindow.reset (new JucyFlutteringJuceMainWindow (getApplicationName()));
        startTimer(1000);
    }

    void shutdown() override                         { jucyFlutteringJuceMainWindow = nullptr; }
    
    void systemRequestedQuit() override
    {
        quit();
    }

    void timerCallback() override
    {
        DBG("timer "+String(i));
        i++;
    }

private:
    std::unique_ptr<JucyFlutteringJuceMainWindow> jucyFlutteringJuceMainWindow;
    int i=0;
};

//==============================================================================
START_JUCE_APPLICATION (JucyFlutteringJuceApplication)
