/*
  ==============================================================================

    IOSAppDelegate.mm
    Created: 22 Sep 2020
    Author:  audiooffler <sp.martin@gmx.net>
 
  ==============================================================================
*/


// import iOS headers before JUCE includes to avoid abiguities for class names
#import "IOSAppDelegate.h"
#include "JucyFlutteringJuceApplication.h"

#if JUCE_IOS

// === JUCE App Entry ==========================================================

// has to be placed in mm file, see https://forum.juce.com/t/custom-delegate-example/39501
START_JUCE_APPLICATION_WITH_CUSTOM_DELEGATE(JucyFlutteringJuceApplication, IOSAppDelegate)

// === interface IOSAppDelegate ================================================

@implementation IOSAppDelegate

// initialize a new object (the receiver) immediately after memory for it has been allocated, https://developer.apple.com/documentation/objectivec/nsobject?language=occ
-(id) init
{
    self = [super init];
    _juceDelegate = reinterpret_cast<NSObject<UIApplicationDelegate>*> ([[NSClassFromString (@"JuceAppStartupDelegate") alloc] init]);
    _lifeCycleDelegate = [[FlutterPluginAppLifeCycleDelegate alloc] init];
    return self;
}

// when launch process is almost done and the app is almost ready to run, https://developer.apple.com/documentation/uikit/uiapplicationdelegate/1622921-application
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions {
  [_juceDelegate applicationDidFinishLaunching:application];
  self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
  self.flutterEngine = [[FlutterEngine alloc] initWithName:@"io.flutter" project:nil];
    // Runs the default Dart entrypoint with a default Flutter route.
  [self.flutterEngine run]; // [self.flutterEngine runWithEntrypoint:nil];
  // Used to connect plugins (only if you have plugins with iOS platform code).
  [GeneratedPluginRegistrant registerWithRegistry:self.flutterEngine];
    
  self.flutterViewController = [[FlutterViewController alloc] initWithEngine:_flutterEngine nibName:nil bundle:nil];
  self.window.rootViewController = _flutterViewController;
  [self.window makeKeyAndVisible];
    
  return [_lifeCycleDelegate application:application didFinishLaunchingWithOptions:launchOptions];
}

// deallocates the memory occupied by the receiver, https://developer.apple.com/documentation/objectivec/nsobject?language=occ
-(void) dealloc
{
    [_juceDelegate release];
    [super dealloc];
}

// forwarding messages to other objects, https://developer.apple.com/documentation/objectivec/nsobject?language=occ
- (void) forwardInvocation: (NSInvocation*) anInvocation
{
    if (_juceDelegate != nullptr && [_juceDelegate respondsToSelector: [anInvocation selector]])
        [anInvocation invokeWithTarget: _juceDelegate];
    else
        [super forwardInvocation: anInvocation];
}

// indicates whether the receiver implements or inherits a method that can respond to a specified message, https://developer.apple.com/documentation/objectivec/1418956-nsobject?language=occ
-(BOOL) respondsToSelector: (SEL) aSelector
{
    if (_juceDelegate != nullptr && [_juceDelegate respondsToSelector: aSelector])
        return YES;

    return [super respondsToSelector: aSelector];
}

// for the further methods, see https://flutter.dev/docs/development/add-to-app/ios/add-flutter-screen?tab=vc-objective-c-tab#using-the-flutterappdelegate

// Returns the key window's rootViewController, if it's a FlutterViewController.
// Otherwise, returns nil.
- (FlutterViewController*)rootFlutterViewController {
    UIViewController* viewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    if ([viewController isKindOfClass:[FlutterViewController class]]) {
        return (FlutterViewController*)viewController;
    }
    return nil;
}

- (void)application:(UIApplication*)application
didRegisterUserNotificationSettings:(UIUserNotificationSettings*)notificationSettings {
    [_lifeCycleDelegate application:application
didRegisterUserNotificationSettings:notificationSettings];
}

- (void)application:(UIApplication*)application
didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken {
    [_lifeCycleDelegate application:application
didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
}

- (void)application:(UIApplication*)application
didReceiveRemoteNotification:(NSDictionary*)userInfo
fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler {
    [_lifeCycleDelegate application:application
       didReceiveRemoteNotification:userInfo
             fetchCompletionHandler:completionHandler];
}

- (BOOL)application:(UIApplication*)application
            openURL:(NSURL*)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey, id>*)options {
    return [_lifeCycleDelegate application:application openURL:url options:options];
}

- (BOOL)application:(UIApplication*)application handleOpenURL:(NSURL*)url {
    return [_lifeCycleDelegate application:application handleOpenURL:url];
}

- (BOOL)application:(UIApplication*)application
            openURL:(NSURL*)url
  sourceApplication:(NSString*)sourceApplication
         annotation:(id)annotation {
    return [_lifeCycleDelegate application:application
                                   openURL:url
                         sourceApplication:sourceApplication
                                annotation:annotation];
}

- (void)application:(UIApplication*)application
performActionForShortcutItem:(UIApplicationShortcutItem*)shortcutItem
  completionHandler:(void (^)(BOOL succeeded))completionHandler NS_AVAILABLE_IOS(9_0) {
    [_lifeCycleDelegate application:application
       performActionForShortcutItem:shortcutItem
                  completionHandler:completionHandler];
}

- (void)application:(UIApplication*)application
handleEventsForBackgroundURLSession:(nonnull NSString*)identifier
  completionHandler:(nonnull void (^)(void))completionHandler {
    [_lifeCycleDelegate application:application
handleEventsForBackgroundURLSession:identifier
                  completionHandler:completionHandler];
}

- (void)application:(UIApplication*)application
performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler {
    [_lifeCycleDelegate application:application performFetchWithCompletionHandler:completionHandler];
}

- (void)addApplicationLifeCycleDelegate:(NSObject<FlutterPlugin>*)delegate {
    [_lifeCycleDelegate addDelegate:delegate];
}

@end

#endif
