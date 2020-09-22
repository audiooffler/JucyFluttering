/*
  ==============================================================================

    IOSAppDelegate.h
    Created: 22 Sep 2020
    Author:  audiooffler <sp.martin@gmx.net>
 
    This is an UIApplicationDelegate for running JUCE and Flutter in an iOS app.
      https://developer.apple.com/documentation/uikit/uiapplicationdelegate
    It deals with setting the main UIWindow with the Flutter View, read here:
      https://flutter.dev/docs/development/add-to-app/ios/add-flutter-screen?tab=vc-objective-c-tab
    It also cares for JUCE, see:
      JUCE/modules/juce_events/messages/juce_Initialisation.h
 
    In the PROJUCER export settings, set binary build dir for the ios targets to $(BUILD_DIR)/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME), see
      https://forum.juce.com/t/solved-cocoapods-and-introjucer-generated-projects-linker-error-react-native/16426
    
    This imports Flutter.h, so after exporting the project with PROJUCER, run
      "pod install" in terminal in Builds/iOS directory and open / compile the
      file "JucyFluttering.xcworkspace" (not .xcpodeproj).

  ==============================================================================
*/

#pragma once

// import iOS headers before JUCE includes to avoid abiguities for class names
#import <UIKit/UIKit.h>
#import <Flutter/Flutter.h>
// Used to connect plugins (only if you have plugins with iOS platform code).
#import <FlutterPluginRegistrant/GeneratedPluginRegistrant.h>


@interface IOSAppDelegate : UIResponder <UIApplicationDelegate, FlutterAppLifeCycleProvider>
@property (nonatomic, strong) NSObject<UIApplicationDelegate> *juceDelegate;
@property (nonatomic, strong) FlutterEngine *flutterEngine;
@property (nonatomic, strong) UIWindow *window;
@property (nonatomic, strong) FlutterViewController *flutterViewController;
@property (nonatomic, strong) FlutterPluginAppLifeCycleDelegate* lifeCycleDelegate;
@end
