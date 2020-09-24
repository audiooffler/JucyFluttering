import 'dart:ffi';
import 'dart:io' show Platform; // For Platform.isAndroid
import 'package:ffi/ffi.dart';

// see https://dart.dev/guides/libraries/c-interop
// Open the dynamic library
final DynamicLibrary juce = () {
  var lib;
  try {
    lib = (Platform.isAndroid)
        ? DynamicLibrary.open(
            'libjuce_jni.so') // for android juce is a dyn. lib
        : DynamicLibrary.process(); // else juce is statically linked;
  } catch (exception) {
    print("Did not find libjuce_jni.so");
    lib = null;
  }
  /*
  if (lib != null) {
    void Function() startJuceApplicationAndEventLoop = lib
        .lookup<NativeFunction<Void Function()>>(
            'startJuceApplicationAndEventLoop')
        .asFunction();
    startJuceApplicationAndEventLoop();
  }*/
  return lib;
}.call();

// see https://pub.flutter-io.cn/packages/ffi/example
String fromUtf8AndFree(Pointer<Utf8> utf8Ptr) {
  String resultString = Utf8.fromUtf8(utf8Ptr);
  free(utf8Ptr);
  return resultString;
}

// Get C function reference, put it into a variable.
final int Function(int numberIn) juceCalcIncrement = (juce == null)
    ? ([int]) => -1111111111 // if juce library not available
    : juce
        .lookup<NativeFunction<Int32 Function(Int32)>>('calcIncrement')
        .asFunction();

final Pointer<Utf8> Function() juceGetAppNameUTF8 = (juce == null)
    ? () => null
    : juce
        .lookup<NativeFunction<Pointer<Utf8> Function()>>('getAppName')
        .asFunction();

String getAppName() {
  if (juce == null) return "";
  // else
  return fromUtf8AndFree(juceGetAppNameUTF8());
}

// === callback example ========================================================

// an actual dart function, to executed from juce via callback
void dartDecrement() {
  print('Dart decrment function was called.');
}

// some function typedefs (for less coding redundancy and better documentation):
// function pointer type for a native/ffi Void function
typedef VoidCallbackT = Void Function();
// Void function type with Void callback function as argument - for native usage
typedef JuceRegisterVoidCallbackT = Void Function(
    Pointer<NativeFunction<VoidCallbackT>>);
// void function with Void callback function as argument - for dart usage
typedef DartRegisterVoidCallbackT = void Function(
    Pointer<NativeFunction<VoidCallbackT>>);

// native function pointer to actual dart function, to be registered as callback
final Pointer<NativeFunction<VoidCallbackT>> dartDecrementCallback =
    Pointer.fromFunction<VoidCallbackT>(dartDecrement);

// dart function pointer to native callback registration function
final DartRegisterVoidCallbackT juceRegisterCallbackFunction = (juce == null)
    ? () => null
    : juce
        .lookup<NativeFunction<JuceRegisterVoidCallbackT>>(
            'registerDartDecrementCallback')
        .asFunction();

/*
// native function type
typedef example_foo = Int32 Function(Int32 bar, Pointer<NativeFunction<example_callback>>);
// dart callback function type
typedef ExampleFoo  = int   Function(int bar,   Pointer<NativeFunction<example_callback>>);

typedef example_callback = Int32 Function(Pointer<Void>, Int32);

//and the code for the callback
int callback(Pointer<Void> ptr, int i) {
  print('in callback i=$i');
  return i + 1;
}

// lookup juce function
ExampleFoo juceFooFunction =
    juce.lookup<NativeFunction<example_foo>>('juceFoo').asFunction();

const exceptionalReturn = -1;

//and, finally, use it like this:
int foo(int i) {
  return juceFooFunction(
    i,
    Pointer.fromFunction<example_callback>(
        callback, exceptionalReturn),
  );
}
*/
