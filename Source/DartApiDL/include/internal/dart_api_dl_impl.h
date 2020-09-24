/*
 * Copyright (c) 2020, the Dart project authors.  Please see the AUTHORS file
 * for details. All rights reserved. Use of this source code is governed by a
 * BSD-style license that can be found in the LICENSE file.
 */

#ifndef RUNTIME_INCLUDE_INTERNAL_DART_API_DL_IMPL_H_
#define RUNTIME_INCLUDE_INTERNAL_DART_API_DL_IMPL_H_

// dart_native_api.h symbols can be called on any thread.
#define DART_NATIVE_API_DL_SYMBOLS(F)                                       \
  /***** dart_native_api.h *****/                                           \
  /* Dart_Port */                                                           \
  F(Dart_PostCObject, bool, (Dart_Port_DL port_id, Dart_CObject * message)) \
  F(Dart_PostInteger, bool, (Dart_Port_DL port_id, int64_t message))        \
  F(Dart_NewNativePort, Dart_Port_DL,                                       \
    (const char *name, Dart_NativeMessageHandler_DL handler,                \
     bool handle_concurrently))                                             \
  F(Dart_CloseNativePort, bool, (Dart_Port_DL native_port_id))

// dart_api.h symbols can only be called on Dart threads.
#define DART_API_DL_SYMBOLS(F)                                              \
  /***** dart_api.h *****/                                                  \
  /* Errors */                                                              \
  F(Dart_IsError, bool, (Dart_Handle handle))                               \
  F(Dart_IsApiError, bool, (Dart_Handle handle))                            \
  F(Dart_IsUnhandledExceptionError, bool, (Dart_Handle handle))             \
  F(Dart_IsCompilationError, bool, (Dart_Handle handle))                    \
  F(Dart_IsFatalError, bool, (Dart_Handle handle))                          \
  F(Dart_GetError, const char *, (Dart_Handle handle))                      \
  F(Dart_ErrorHasException, bool, (Dart_Handle handle))                     \
  F(Dart_ErrorGetException, Dart_Handle, (Dart_Handle handle))              \
  F(Dart_ErrorGetStackTrace, Dart_Handle, (Dart_Handle handle))             \
  F(Dart_NewApiError, Dart_Handle, (const char *error))                     \
  F(Dart_NewCompilationError, Dart_Handle, (const char *error))             \
  F(Dart_NewUnhandledExceptionError, Dart_Handle, (Dart_Handle exception))  \
  F(Dart_PropagateError, void, (Dart_Handle handle))                        \
  /* Dart_Handle, Dart_PersistentHandle, Dart_WeakPersistentHandle */       \
  F(Dart_HandleFromPersistent, Dart_Handle, (Dart_PersistentHandle object)) \
  F(Dart_HandleFromWeakPersistent, Dart_Handle,                             \
    (Dart_WeakPersistentHandle object))                                     \
  F(Dart_NewPersistentHandle, Dart_PersistentHandle, (Dart_Handle object))  \
  F(Dart_SetPersistentHandle, void,                                         \
    (Dart_PersistentHandle obj1, Dart_Handle obj2))                         \
  F(Dart_DeletePersistentHandle, void, (Dart_PersistentHandle object))      \
  F(Dart_NewWeakPersistentHandle, Dart_WeakPersistentHandle,                \
    (Dart_Handle object, void *peer, intptr_t external_allocation_size,     \
     Dart_WeakPersistentHandleFinalizer callback))                          \
  F(Dart_DeleteWeakPersistentHandle, void,                                  \
    (Dart_WeakPersistentHandle object))                                     \
  F(Dart_UpdateExternalSize, void,                                          \
    (Dart_WeakPersistentHandle object, intptr_t external_allocation_size))  \
  F(Dart_NewFinalizableHandle, Dart_FinalizableHandle,                      \
    (Dart_Handle object, void *peer, intptr_t external_allocation_size,     \
     Dart_HandleFinalizer callback))                                        \
  F(Dart_DeleteFinalizableHandle, void,                                     \
    (Dart_FinalizableHandle object, Dart_Handle strong_ref_to_object))      \
  F(Dart_UpdateFinalizableExternalSize, void,                               \
    (Dart_FinalizableHandle object, Dart_Handle strong_ref_to_object,       \
     intptr_t external_allocation_size))                                    \
  /* Dart_Port */                                                           \
  F(Dart_Post, bool, (Dart_Port_DL port_id, Dart_Handle object))            \
  F(Dart_NewSendPort, Dart_Handle, (Dart_Port_DL port_id))                  \
  F(Dart_SendPortGetId, Dart_Handle,                                        \
    (Dart_Handle port, Dart_Port_DL * port_id))                             \
  /* Scopes */                                                              \
  F(Dart_EnterScope, void, ())                                              \
  F(Dart_ExitScope, void, ())

#define DART_API_ALL_DL_SYMBOLS(F) \
  DART_NATIVE_API_DL_SYMBOLS(F)    \
  DART_API_DL_SYMBOLS(F)

typedef struct
{
  const char *name;
  void (*function)();
} DartApiEntry;

typedef struct
{
  const int32_t major;
  const int32_t minor;
  const DartApiEntry *const functions;
} DartApi;

#endif /* RUNTIME_INCLUDE_INTERNAL_DART_API_DL_IMPL_H_ */ /* NOLINT */
