// Automatically generated from ../../../Source/JavaScriptCore/runtime/DateConstructor.cpp using /home/harry/WebKit-r89332/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const struct HashTableValue dateConstructorTableValues[4] = {
   { "parse", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(dateParse), (intptr_t)1 THUNK_GENERATOR(0) },
   { "UTC", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(dateUTC), (intptr_t)7 THUNK_GENERATOR(0) },
   { "now", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(dateNow), (intptr_t)0 THUNK_GENERATOR(0) },
   { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
extern JSC_CONST_HASHTABLE HashTable dateConstructorTable =
    { 9, 7, dateConstructorTableValues, 0 };
} // namespace
