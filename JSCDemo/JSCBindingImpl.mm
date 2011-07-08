//
//  JSCBindling.cpp
//  JNIDemo
//
//  Created by Rob Evans
//  Copyright 2011 Irrelon Software Limited
//	http://www.isogenicengine.com

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

#include "JSCBindingImpl.h"
#include "Completion.h"
#include "CurrentTime.h"
#include "ExceptionHelpers.h"
#include "InitializeThreading.h"
#include "JSArray.h"
#include "JSFunction.h"
#include "JSLock.h"
#include "JSString.h"
#include "Error.h"
#include "SourceCode.h"

#include <string>

#if ENABLE(JSC_MULTIPLE_THREADS) 
#endif

using namespace JSC;

static EncodedJSValue JSC_HOST_CALL functionPrint(ExecState*);
static EncodedJSValue JSC_HOST_CALL functionCallObjc(ExecState* exec);

static bool fillBufferWithContentsOfFile(const UString& fileName, Vector<char>& buffer);

class GlobalObject : public JSGlobalObject {
public:
    GlobalObject(JSGlobalData&, Structure*);
    virtual UString className() const { return "global"; }
};

GlobalObject::GlobalObject(JSGlobalData& globalData, Structure* structure)
: JSGlobalObject(globalData, structure)
{   
    putDirectFunction(globalExec(), new (globalExec()) JSFunction(globalExec(), this, functionStructure(), 1, Identifier(globalExec(), "print"), functionPrint));
    putDirectFunction(globalExec(), new (globalExec()) JSFunction(globalExec(), this, functionStructure(), 1, Identifier(globalExec(), "callObjc"), functionCallObjc));
    
}

#import "JSCBinding.h"
EncodedJSValue JSC_HOST_CALL functionCallObjc(ExecState* exec)
{

   NSString* ret =  [[JSCBinding shareInstance].delegate execObjectC:[NSString stringWithFormat:@"%s",exec->argument(0).toString(exec).utf8().data()]];
        
	return JSValue::encode(jsString(exec, UString([ret UTF8String])));
}

EncodedJSValue JSC_HOST_CALL functionPrint(ExecState* exec)
{
    for (unsigned i = 0; i < exec->argumentCount(); ++i) {
        if (i)
            putchar(' ');
        
        [[JSCBinding shareInstance].delegate print:[NSString stringWithFormat:@"%s",exec->argument(i).toString(exec).utf8().data()]];
        
    }
    
    putchar('\n');
    fflush(stdout);
    return JSValue::encode(jsNumber(0));
}

static bool fillBufferWithContentsOfFile(const UString& fileName, Vector<char>& buffer)
{
    FILE* f = fopen(fileName.utf8().data(), "r");
    if (!f) {
        NSLog(@"Could not open file: %s\n", fileName.utf8().data());
        return false;
    }
    
    size_t bufferSize = 0;
    size_t bufferCapacity = 1024;
    
    buffer.resize(bufferCapacity);
    
    while (!feof(f) && !ferror(f)) {
        bufferSize += fread(buffer.data() + bufferSize, 1, bufferCapacity - bufferSize, f);
        if (bufferSize == bufferCapacity) { // guarantees space for trailing '\0'
            bufferCapacity *= 2;
            buffer.resize(bufferCapacity);
        }
    }
    fclose(f);
    buffer[bufferSize] = '\0';
    
    if (buffer[0] == '#' && buffer[1] == '!')
        buffer[0] = buffer[1] = '/';
    
    return true;
}

JSCBindingImpl::JSCBindingImpl()
{
    // Initialize JSC before getting JSGlobalData.
    JSC::initializeThreading();

    m_globalData = JSGlobalData::create(ThreadStackTypeSmall).leakRef();
    m_globalObject = new (m_globalData) GlobalObject(*m_globalData, GlobalObject::createStructure(*m_globalData, jsNull()));
    
}

JSCBindingImpl::~JSCBindingImpl()
{
    m_globalData->clearBuiltinStructures();
    m_globalData->heap.destroy();
    m_globalData->deref();

}

int JSCBindingImpl::load(const char* jsfile)
{
    Vector<char> script;
    if (!fillBufferWithContentsOfFile(jsfile, script))
        return -1;

    Completion result = evaluate(m_globalObject->globalExec(), m_globalObject->globalScopeChain(), makeSource(script.data(), jsfile));
    
    if (result.complType() == Throw)
    {
        //throwError(m_globalObject->globalExec(), result.value());
        //return -1;
        NSLog(@"Exception: %s",result.value().toString(m_globalObject->globalExec()).utf8().data());
        return -1;
    }
    
    return 0;
}

std::string  JSCBindingImpl::exec(const char* script)
{
    std::string ret;
    
    Completion result = evaluate(m_globalObject->globalExec(), m_globalObject->globalScopeChain(), makeSource(script));
    
    
    if(result.complType() ==  Throw) {
        //printf("Exception")
        NSLog(@"Exception: %s",result.value().toString(m_globalObject->globalExec()).utf8().data());
    }
    else {
        ret = std::string(result.value().toString(m_globalObject->globalExec()).utf8().data());
    }
    
    return ret;
}

