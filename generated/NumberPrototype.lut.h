// Automatically generated from ../../../Source/JavaScriptCore/runtime/NumberPrototype.cpp using /home/harry/WebKit-r89332/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const struct HashTableValue numberPrototypeTableValues[7] = {
   { "toString", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(numberProtoFuncToString), (intptr_t)1 THUNK_GENERATOR(0) },
   { "toLocaleString", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(numberProtoFuncToLocaleString), (intptr_t)0 THUNK_GENERATOR(0) },
   { "valueOf", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(numberProtoFuncValueOf), (intptr_t)0 THUNK_GENERATOR(0) },
   { "toFixed", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(numberProtoFuncToFixed), (intptr_t)1 THUNK_GENERATOR(0) },
   { "toExponential", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(numberProtoFuncToExponential), (intptr_t)1 THUNK_GENERATOR(0) },
   { "toPrecision", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(numberProtoFuncToPrecision), (intptr_t)1 THUNK_GENERATOR(0) },
   { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
extern JSC_CONST_HASHTABLE HashTable numberPrototypeTable =
    { 17, 15, numberPrototypeTableValues, 0 };
} // namespace
