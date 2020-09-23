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
  return lib;
}.call();

// see https://pub.flutter-io.cn/packages/ffi/example
String fromUtf8AndFree(Pointer<Utf8> utf8Ptr) {
  String resultString = Utf8.fromUtf8(utf8Ptr);
  free(utf8Ptr);
  return resultString;
}

// Get C function reference, put it into a variable.
final int Function(int numberIn) juceIncrement = (juce == null)
    ? ([int]) => -1111111111 // if juce library not available
    : juce
        .lookup<NativeFunction<Int32 Function(Int32)>>('increment')
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
