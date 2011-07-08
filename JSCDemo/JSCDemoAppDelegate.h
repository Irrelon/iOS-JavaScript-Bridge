//
//  JSCDemoAppDelegate.h
//  JSCDemo
//
//  Created by Rob Evans
//  Copyright 2011 Irrelon Software Limited
//	http://www.isogenicengine.com

#import <UIKit/UIKit.h>

@class JSCDemoViewController;

@interface JSCDemoAppDelegate : NSObject <UIApplicationDelegate> {

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet JSCDemoViewController *viewController;

@end
