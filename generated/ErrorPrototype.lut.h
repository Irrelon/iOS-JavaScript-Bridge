// Automatically generated from ../../../Source/JavaScriptCore/runtime/ErrorPrototype.cpp using /home/harry/WebKit-r89332/Source/JavaScriptCore/create_hash_table. DO NOT EDIT!

#include "Lookup.h"

namespace JSC {
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const struct HashTableValue errorPrototypeTableValues[2] = {
   { "toString", DontEnum|Function, (intptr_t)static_cast<NativeFunction>(errorProtoFuncToString), (intptr_t)0 THUNK_GENERATOR(0) },
   { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
extern JSC_CONST_HASHTABLE HashTable errorPrototypeTable =
    { 2, 1, errorPrototypeTableValues, 0 };
} // namespace
