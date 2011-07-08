//
//  JSCBindingInterface.m
//  JNIDemo
//
//  Created by Rob Evans
//  Copyright 2011 Irrelon Software Limited
//	http://www.isogenicengine.com

#import "JSCBinding.h"

#import "JSCBindingImpl.h"

@implementation JSCBinding
@synthesize delegate;

static JSCBindingImpl * bindingimpl = 0;
static JSCBinding * selfInstance = nil;

+(id) hideAlloc
{
    return [super alloc];
}

+(id) alloc
{
    NSLog(@"use +shareInstace instand of +alloc");
    return nil;
}

+(id) new
{
    return [self alloc];
}

-(id) copyWithZone:(NSZone *)zone
{
    NSLog(@"attemp to -copy may be a bug");
    [self retain];
    return self;
}

-(id) mutableCopyWithZone:(NSZone*) zone
{
    return [self copyWithZone:zone];
}

- (void)dealloc {
    delete bindingimpl;
    [super dealloc];
}


+(JSCBinding*) shareInstance
{
    if (selfInstance == nil) {
        selfInstance = [[[self class] hideAlloc] init];
    }
    
    return selfInstance;
}

+ (void) attemptDealloc
{
    if ([selfInstance retainCount] != 1) {
        return;
    }
    
    [selfInstance release];
    selfInstance = nil;
}

+ (BOOL) shareInstanceExists
{
    return (nil != selfInstance);
}

- (id)init {
    self = [super init];
    if (self) {
        bindingimpl = new JSCBindingImpl();
    }
    return self;
}

-(int) load:(NSString*)jsfile
{
   return bindingimpl->load([jsfile UTF8String]);
}


-(NSString*) execJavaScrpt:(NSString*)script
{
    std::string ret = bindingimpl->exec([script UTF8String]);
    
    return [NSString stringWithFormat:@"%s",ret.c_str()];
}


@end
