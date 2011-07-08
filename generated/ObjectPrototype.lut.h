// Automatically generated from ../../../Source/JavaScriptCore/runtime/ObjectPrototype.cpp using /home/harry/WebKit-r89332/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const struct HashTableValue objectPrototypeTableValues[11] = {
   { "toString", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncToString), (intptr_t)0 THUNK_GENERATOR(0) },
   { "toLocaleString", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncToLocaleString), (intptr_t)0 THUNK_GENERATOR(0) },
   { "valueOf", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncValueOf), (intptr_t)0 THUNK_GENERATOR(0) },
   { "hasOwnProperty", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncHasOwnProperty), (intptr_t)1 THUNK_GENERATOR(0) },
   { "propertyIsEnumerable", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncPropertyIsEnumerable), (intptr_t)1 THUNK_GENERATOR(0) },
   { "isPrototypeOf", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncIsPrototypeOf), (intptr_t)1 THUNK_GENERATOR(0) },
   { "__defineGetter__", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncDefineGetter), (intptr_t)2 THUNK_GENERATOR(0) },
   { "__defineSetter__", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncDefineSetter), (intptr_t)2 THUNK_GENERATOR(0) },
   { "__lookupGetter__", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncLookupGetter), (intptr_t)1 THUNK_GENERATOR(0) },
   { "__lookupSetter__", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(objectProtoFuncLookupSetter), (intptr_t)1 THUNK_GENERATOR(0) },
   { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
extern JSC_CONST_HASHTABLE HashTable objectPrototypeTable =
    { 32, 31, objectPrototypeTableValues, 0 };
} // namespace
