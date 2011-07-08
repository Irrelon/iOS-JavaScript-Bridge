// Automatically generated from ../../../Source/JavaScriptCore/runtime/JSGlobalObject.cpp using /home/harry/WebKit-r89332/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const struct HashTableValue globalObjectTableValues[11] = {
   { "parseInt", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncParseInt), (intptr_t)2 THUNK_GENERATOR(0) },
   { "parseFloat", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncParseFloat), (intptr_t)1 THUNK_GENERATOR(0) },
   { "isNaN", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncIsNaN), (intptr_t)1 THUNK_GENERATOR(0) },
   { "isFinite", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncIsFinite), (intptr_t)1 THUNK_GENERATOR(0) },
   { "escape", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncEscape), (intptr_t)1 THUNK_GENERATOR(0) },
   { "unescape", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncUnescape), (intptr_t)1 THUNK_GENERATOR(0) },
   { "decodeURI", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncDecodeURI), (intptr_t)1 THUNK_GENERATOR(0) },
   { "decodeURIComponent", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncDecodeURIComponent), (intptr_t)1 THUNK_GENERATOR(0) },
   { "encodeURI", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncEncodeURI), (intptr_t)1 THUNK_GENERATOR(0) },
   { "encodeURIComponent", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(globalFuncEncodeURIComponent), (intptr_t)1 THUNK_GENERATOR(0) },
   { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
extern JSC_CONST_HASHTABLE HashTable globalObjectTable =
    { 34, 31, globalObjectTableValues, 0 };
} // namespace
