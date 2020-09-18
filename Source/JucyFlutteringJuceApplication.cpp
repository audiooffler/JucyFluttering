#include <JuceHeader.h>
#include "JucyFlutteringJuceMainWindow.h"
#include "JucyFlutteringJuceComponent.h"

class JucyFlutteringJuceApplication    : public juce::JUCEApplication
{
public:
    //==============================================================================
    JucyFlutteringJuceApplication() = default;

    const juce::String getApplicationName() override       { return "JucyFluttering"; }
    const juce::String getApplicationVersion() override    { return "0.0.1"; }

    void initialise (const juce::String&) override
    {
        jucyFlutteringJuceMainWindow.reset (new JucyFlutteringJuceMainWindow (getApplicationName()));
    }

    void shutdown() override                         { jucyFlutteringJuceMainWindow = nullptr; }
    
    void systemRequestedQuit() override
    {
        quit();
    }

private:
    std::unique_ptr<JucyFlutteringJuceMainWindow> jucyFlutteringJuceMainWindow;
};

//==============================================================================
START_JUCE_APPLICATION (JucyFlutteringJuceApplication)
