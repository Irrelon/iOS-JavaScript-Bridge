//
//  JSCBindling.h
//  JNIDemo
//
//  Created by Rob Evans
//  Copyright 2011 Irrelon Software Limited
//	http://www.isogenicengine.com

#ifndef __JSCBINDING_H__
#define __JSCBINDING_H__

#include <string>

class JSCBindingImplPri;

namespace JSC {
    class JSGlobalData;
}

class GlobalObject;
class JSCBindingDelegate;

class JSCBindingImpl
{
public:
    JSCBindingImpl();
    ~JSCBindingImpl();
    int load(const char* jsfile);
    std::string exec(const char* script);
    void test(){} 
private:
    JSC::JSGlobalData* m_globalData ;
    GlobalObject* m_globalObject ;
};

#endif
