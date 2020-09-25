# Jucy Fluttering

A simple mobile app example (iOS, Android) that uses a Flutter (Dart) UI and JUCE (C++) as backend.

## Project Setup and Boilerplates

- Created a JUCE GUI project `JucyFluttering` with Android and iOS exporters (well it does not really show a GUI, but has a message loop running, to provide timers, event handling etc.)

- Created a flutter plugin project (subfolder `fluttering`) for platforms android and iOs, using  Java for android, and ObjectiveC for iOS
  - `flutter create --template=plugin --platforms=android,ios -a java -i objc fluttering`
  - the .dart source file are placed in `fluttering/lib`

JUCE is already does a good job at setting up all the platform-dependend boilerplate code to instantiate and run iOs and Android apps. Some adjustments had to be done to do the Flutter instantiation part too, as documented here:
 - [Adding Flutter to Android](https://flutter.dev/docs/development/add-to-app/android) 
 -  [Adding Flutter to iOS](https://flutter.dev/docs/development/add-to-app/ios/)

### Android Application and Android Activity

Made custom activity and application Java class files, placed in `Sources/Android`. 
 - The Actvity extends the FlutteringActivity class
 - The Application initialises JUCE, but also and instantiates, pre-warms and caches the Flutter Engine, and sets the initial Flutter navigation route to '`/`'

### Android Exporter Setup in Projucer Project and Android Gradle

Some manual configuration for the Projucers Android exporter was necessary:
- Java Source code folders:
  ``` 
  Source/Android
  ```

- Custom Android Activity:
    ```
    eu.selfhost.audiooffler.jucyfluttering.FlutteringActivity
    ```

- Custom Android Application:
    ```
    eu.selfhost.audiooffler.jucyfluttering.FlutteringApplication
    ```

-  Module Dependencies:
   ```
   implementation project(':flutter')
   ```
  
- Extra module's build.gradle content: 
    ```
    defaultConfig {
        ndk {
            // filter for architectures supported by Flutter
            abiFilters 'armeabi-v7a', 'arm64-v8a', 'x86', 'x86_64'
        }
    }

    compileOptions {
        // Flutter Android engine uses Java 8 features
        sourceCompatibility 1.8
        targetCompatibility 1.8
    }
    ```
- Custom settings.gradle content:
    ```
    setBinding(new Binding([gradle: this]))
    evaluate(new File(
        settingsDir.parentFile.parentFile,
        'fluttering/.android/include_flutter.groovy'
    ))
    ```
- Android Theme:
  ```
  @android:style/Theme.NoTitleBar
  ```

Projucer can't create / manipulate a `gradle.properties` file, but this is needed for Flutter
 - The file with the following content was manually placed at `Builds/Android` folder of this repository, it won't get overwritten by the Projucre, just do not delete it manually:

    ```
    android.useAndroidX=true
    android.enableJetifier=true
    ```

### iOS UIApplicationDelegate

Made a custom App Delegate class, placed at `Sources/iOS`. This is an [UIApplicationDelegate](https://developer.apple.com/documentation/uikit/uiapplicationdelegate) for running JUCE and Flutter in an iOS app. It's `.mm` File also has the `START_JUCE_APPLICATION_WITH_CUSTOM_DELEGATE` call to automatically start the JUCEApplication with this Delegate, `as documented in JUCE/modules/juce_events/messages/juce_Initialisation.h`. The delegate takes care of:
- Juce Initialisation and handling
- Flutter Engine Initalisation and handling
- UIWindow ([showing the Flutter View](https://flutter.dev/docs/development/add-to-app/ios/add-flutter-screen?tab=vc-objective-c-tab))
- FlutterViewController
- FlutterPluginAppLifeCycleDelegate

### iOS CocooaPods and iOS Exporter Setup in Projucer Project 

CocoaPods is needed for FLutter integration. 
- If do not have it installed yet (check with `which pod`), do so with `sudo gem install cocoapod`
- A Podfile was made manually and placed in this repository (`Builds/iOS/Podfile`), containing the following. The Projucer won't overwite it, just do not delete it manually.
  ```
    platform :ios, '9.0'

    flutter_application_path = '../../fluttering'
    load File.join(flutter_application_path, '.ios', 'Flutter', 'podhelper.rb')

    target 'Jucy Fluttering - App' do
    
    install_all_flutter_pods(flutter_application_path)

    end
  ```

In Projucer, some iOS export settings had to be configured:
- To make it work with CocoaPods (as found in adamski's thread in the [JUCE forum](https://forum.juce.com/t/solved-cocoapods-and-introjucer-generated-projects-linker-error-react-native/16426)), for all build target configuations (Release/Debug), set Binary Location:
  ```
  $(BUILD_DIR)/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)
  ```
- Custom PList
    ```
    <plist>
        <dict>
            <key>UIBackgroundModes</key>
            <array>
                <string>fetch</string>
                <string>remote-notification</string>
            </array>
        </dict>
    </plist>
    ```
## Build and Debug

### Android    

No extra steps needed building. The project can be opened with Android Studio from the Projucer or by opening the `Builds/Android` project folder in Android Studio.
If dart support is enabled for the project in Android Studio, it even attaches the flutter debugger.
Else, while running / debugging, one may call `flutter attach ` from terminal (first go to `cd ./fluttering`).

### iOS

After saving / exporting with Projucer, the XCode Project can't simply be build as usual for JUCE projects. Two more steps are necassary:
- from terminal **run `pod install`** (first go to `cd ./Builds/iOS`)
- then **open the generated `.xcworkspace` project** and build that
  - the .xcodeproj would fail, due to the missing Flutter dependencies

While running / debugging from xCode, one may call `flutter attach ` from terminal (first go to `cd ./fluttering`).

## Calls and Messages between JUCE/C++ and Flutter/Dart

Check out the [Flutter/dart:ffi documentation](https://flutter.dev/docs/development/platform-integration/c-interop) for the basic setup of accessing nativ C++ code from Flutter/dart.

Some examples can be found in `Sources/JucyFlutteringInterop.h` and the dart counterparts in `fluttering/lib/juce_fluttering_interop.dart`.

### Dart code for executing simple JUCE/C++ functions
- Externalized JUCE/C++ functions can be called from Fluttter/Dart via [dart:ffi NativeFunction](https://dart.dev/guides/libraries/c-interop)s, since the dart isolate (thread) will execute it.
- Some boilercode / wrapping is still needed. See `fluttering/lib/juce_fluttering_interop.dart`.

### Getting Strings from JUCE/C++ into dart
- For getting `juce::Strings`, JUCE has to return UTF-8 char* pointers
- If the String is local it has to be copied to memory or it will get lost on return. 
- This can be done using `toRawUTF8`, `malloc` and `strcpy`, see the example in `EXTERN_C const char *getAppName()` in `Source/JucyFlutteringInterop.h`, using the helper function `const char *copyStringToUTF8(String juceString)` from the same file
- The dart caller then can convert this to a dart String, using `fromUtf8` and call `free` on the returned `Pointer<Utf8>`, utilizing  [import `package:ffi/ffi.dart`](https://pub.dev/packages/ffi). See tthe example in `fluttering/lib/juce_fluttering_interop.dart`

### Asynchronous Messages from JUCE/C++ to Flutter (instead of callbacks)

Problem:
- Access to classes and values is only allowed from the same isolate! 
- JUCE Message Loop (e.g. `juce::Timer`) or AudioCallback Threads (e.g. `juce::AudioProcessor`) won't run in the same isolate as Flutter/Dart UI.
- Therefore, just registering callback [dart:ffi function pointers](https://api.flutter.dev/flutter/dart-ffi/Pointer/fromFunction.html) in your JUCE/C++ code will ***not*** be sufficient. (Except if the callback was called from some C++ function that was started from dart).

Solution:

- Different isolates can communicate by sending values through ports (see [ReceivePort](https://api.flutter.dev/flutter/dart-isolate/ReceivePort-class.html), [SendPort](https://api.flutter.dev/flutter/dart-isolate/SendPort-class.html)).
- To access the dart native API from C++, files from
[GitHub: dart-lang/sdk/runtime/include](https://github.com/dart-lang/sdk/tree/master/runtime/include) where included in the JUCE project [Source/DartApiDL](file://./Source/DartApiDL/) (the folder was added to the header search paths for all Build/Debug targets). see https://github.com/mraleph/go_dart_ffi_example
- Init by calling the NativeAPI from dart (that will be the receiver) and tell JUCE/C++ the port.
- From then on JUCE/C++ may send messages containing objects with int, double or UTF-8 char* string pointers to the dart receiver port.