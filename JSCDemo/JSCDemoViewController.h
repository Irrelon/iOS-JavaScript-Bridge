//
//  JSCDemoViewController.h
//  JSCDemo
//
//  Created by Rob Evans
//  Copyright 2011 Irrelon Software Limited
//	http://www.isogenicengine.com

#import <UIKit/UIKit.h>
#import "JSCBinding.h"

@interface JSCDemoViewController : UIViewController <JSCBindingDelegate> {
    UITextView* log;
    UITextField* input;
    UIButton* execButton;
}

@property (nonatomic, retain) IBOutlet UITextView* log;
@property (nonatomic, retain) IBOutlet UITextField* input;
@property (nonatomic, retain) IBOutlet UIButton* execButton;

-(IBAction) press:(id) sender;
-(IBAction) textFiledDown:(id) sender;
@end
