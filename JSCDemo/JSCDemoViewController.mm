//
//  JSCDemoViewController.m
//  JSCDemo
//
//  Created by Rob Evans
//  Copyright 2011 Irrelon Software Limited
//	http://www.isogenicengine.com

#import "JSCDemoViewController.h"
#import "JSCBinding.h"

@implementation JSCDemoViewController
@synthesize log;
@synthesize input;
@synthesize execButton;

- (id)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    if (self) {
        [JSCBinding shareInstance].delegate = self;
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

-(IBAction) press:(id) sender
{
    NSString* result = nil;
    
    UIButton* button =(UIButton*) sender;
    NSString* text = button.titleLabel.text;
    
    if ([text isEqualToString:@"clean"]) {
        log.text = @"";
        return;
    }
    

    
    if ([text isEqualToString:@"test1"]) {
        result = [[JSCBinding shareInstance] execJavaScrpt:@"test1();"];
    }
    
    if ([text isEqualToString:@"test2"]) {
       result = [[JSCBinding shareInstance] execJavaScrpt:@"test2();"];
    }
    
    if ([text isEqualToString:@"test3"]) {
       result = [[JSCBinding shareInstance] execJavaScrpt:@"print(callObjc('call callObjc directly'));"];
        
    }
    
    if ([text isEqualToString:@"test4"]) {
            result = [[JSCBinding shareInstance] execJavaScrpt:@"test4();"];
    }
    
    if ([text isEqualToString:@"exec"]) {
        result = [[JSCBinding shareInstance] execJavaScrpt:input.text];
    }
    
    if ([text isEqualToString:@"Destroy"]) {
        [JSCBinding attemptDealloc];
        log.text = @"";
    }
    
    if ([text isEqualToString:@"Reload"]) {
        
        //When you reload JS you must register delegate at first
        [JSCBinding shareInstance].delegate = self;
        [[JSCBinding shareInstance]  load:[[NSBundle mainBundle] pathForResource:@"demo" ofType:@"js" inDirectory:@"www"]];
    }
    
    NSLog(@"result:%@",result);

}

-(IBAction) textFiledDown:(id) sender
{
    [sender resignFirstResponder];
}
#pragma mark - View lifecycle


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];

    [[JSCBinding shareInstance]  load:[[NSBundle mainBundle] pathForResource:@"demo" ofType:@"js" inDirectory:@"www"]];
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (NSString*) execObjectC:(NSString*) msg
{
    

    return [NSString stringWithFormat:@"execObjectC with msg : %@",msg];
    //output.text = msg;
}

-(void) print:(NSString *)msg
{
    log.text = [NSString stringWithFormat:@"%@\n%@",log.text,msg];
}
@end
