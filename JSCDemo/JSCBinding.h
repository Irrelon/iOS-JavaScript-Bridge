//
//  JSCBindingInterface.h
//  JNIDemo
//
//  Created by Rob Evans
//  Copyright 2011 Irrelon Software Limited
//	http://www.isogenicengine.com

#import <Foundation/Foundation.h>

@protocol JSCBindingDelegate
//JavaScript -> Object C
-(NSString*) execObjectC:(NSString*) data;
//Used by JS print() funtion
-(void) print : (NSString*) msg;
@end

@interface JSCBinding : NSObject {
    id <JSCBindingDelegate> delegate;
}

@property (nonatomic, assign) id <JSCBindingDelegate> delegate;

+ (JSCBinding*) shareInstance;
+ (void) attemptDealloc;
+ (BOOL) shareInstanceExists;

-(int) load:(NSString*)jsfile;
-(NSString*) execJavaScrpt:(NSString*)script;

@end
