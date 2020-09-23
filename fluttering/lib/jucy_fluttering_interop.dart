import 'dart:ffi';
import 'dart:io'; // For Platform.isAndroid

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

// Get C function reference, put it into a variable.
final int Function(int numberIn) juceIncrement = (juce == null)
    ? ([int]) => -1111111111 // if juce library not available
    : juce
        .lookup<NativeFunction<Int32 Function(Int32)>>('increment')
        .asFunction();
