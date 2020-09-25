import 'dart:ffi';
import 'dart:io' show Platform; // For Platform.isAndroid
import 'package:ffi/ffi.dart';
import 'dart:isolate';

// loading juce library and also initialising native messanging
DynamicLibrary loadJuceLibrary() {
  DynamicLibrary lib;
  try {
    lib = (Platform.isAndroid)
        ? DynamicLibrary.open('libjuce_jni.so')
        : // for android juce is a dyn. lib
        DynamicLibrary.process(); // else juce is statically linked;
  } catch (e) {}
  if (lib == null) {
    print('unable to load juce library');
  } else {
    print('dart loaded juce lib');
    initNativeMessenging(lib);
  }

  return lib;
}

// messenging, see https://github.com/mraleph/go_dart_ffi_example
void initNativeMessenging(DynamicLibrary juce) async {
  // initialize the native dart API
  final initializeApi = juce.lookupFunction<IntPtr Function(Pointer<Void>),
      int Function(Pointer<Void>)>("InitializeDartApi");
  if (initializeApi(NativeApi.initializeApiDLData) != 0) {
    throw "Failed to initialize Dart API";
  }

  final interactiveCppRequests = ReceivePort()
    ..listen((data) {
      print('Seconds of JUCE running: ${data}');
    });

  final int nativePort = interactiveCppRequests.sendPort.nativePort;

  final void Function(int port) setDartApiMessagePort = juce
      .lookup<NativeFunction<Void Function(Int64 port)>>(
          "SetDartApiMessagePort")
      .asFunction();
  setDartApiMessagePort(nativePort);
}

final juce = loadJuceLibrary();

// === String result conversion helper function ================================

// see https://pub.flutter-io.cn/packages/ffi/example
String fromUtf8AndFree(Pointer<Utf8> utf8Ptr) {
  String resultString = Utf8.fromUtf8(utf8Ptr);
  free(utf8Ptr);
  return resultString;
}

// === simple c++ function calls ==============================================

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
// some callback - but this will only work if the c++ work was also run
// from dart, not if the JUCE message loop thread wants to call back!

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
