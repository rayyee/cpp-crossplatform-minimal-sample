//
//  ViewController.m
//  ComboSample
//
//  Copyright (c) 2014 Google. All rights reserved.
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#import "ViewController.h"

static NSString * const kClientID = @"YOUR_CLIENT_ID";

@interface ViewController ()

// C++ properties must be declared in the *.mm file and not the *.h file.
@property (atomic) GLDrawer *gld;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Configure platform configuration for iOS
    gpg::IosPlatformConfiguration config;
    config.SetClientID(std::string([kClientID UTF8String]));
    config.SetOptionalViewControllerForPopups(self);

    // Initialize Google Play Games Services with callbacks for Auth operations.  This will
    // attempt to silently sign-in the user if they have signed in before.
    StateManager::InitServices(config,
                               [self](gpg::AuthOperation op) {
                                   [self onAuthActionStarted:op];
                               },
                               [self](gpg::AuthOperation op, gpg::AuthStatus status) {
                                   [self onAuthActionFinished:op withStatus:status];
                               });

    // Enable/disable buttons based on sign-in state.
    [self setButtonState];

    // Set-up OpenGL
    [self setupGL];

}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    self.gld->onDrawFrame();
}

- (void)glkViewControllerUpdate:(GLKViewController *)controller {
    self.gld->onUpdate();
}

- (void)setupGL {
    NSLog(@"Initializing OpenGL View and Context");
    // Initialize the GLKView and set the OpenGL context
    self.glkView.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    self.glkView.delegate = self;
    [EAGLContext setCurrentContext:self.glkView.context];

    NSLog(@"Initializing GLDrawer");
    // Create a C++ GLDrawer object and call the set-up methpds.
    self.gld = new GLDrawer();
    self.gld->onSurfaceCreated();
    self.gld->onSurfaceChanged();

    NSLog(@"Initializing GLKViewController");
    // Instantiate a GLKViewController which will control the render loop for the GLKView.  Set
    // this ViewController as the delegate and add the GLKViewController as a child so that it
    // is displayed.
    GLKViewController * viewController = [[GLKViewController alloc] initWithNibName:nil bundle:nil];
    viewController.view = self.glkView;
    viewController.delegate = self;
    viewController.preferredFramesPerSecond = 30;
    [self addChildViewController:viewController];
}

- (void)setButtonState {
    // Enable/disable buttons based on sign-in state.
    bool signedIn = StateManager::GetGameServices()->IsAuthorized();
    self.signInButton.enabled = !signedIn;
    self.signOutButton.enabled = signedIn;
    self.showAchievementsButton.enabled = signedIn;
    self.showLeaderboardsButton.enabled = signedIn;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)signInButtonWasPressed:(id)sender {
    // Call the C++ sign-in method
    NSLog(@"Sign-in pressed");
    StateManager::BeginUserInitiatedSignIn();
}

- (IBAction)signOutButtonWasPressed:(id)sender {
    // Call the C++ sign-out method
    NSLog(@"Sign-out pressed");
    StateManager::SignOut();
}

- (IBAction)showAchievementsButtonWasPressed:(id)sender {
    // Call the C++ show achievements method
    NSLog(@"Show Achievements pressed");
    StateManager::ShowAchievements();
}

- (IBAction)showLeaderboardsButtonWasPressed:(id)sender {
    // Call the C++ show leaderboards method
    NSLog(@"Show Leaderboards pressed");
    StateManager::ShowLeaderboards();
}

- (void)onAuthActionStarted:(gpg::AuthOperation)op {
    NSLog(@"Auth Action Started");
}

- (void)onAuthActionFinished:(gpg::AuthOperation)op withStatus:(gpg::AuthStatus)status {
    NSLog(@"Auth Action Finished");
    dispatch_async(dispatch_get_main_queue(), ^{
        [self setButtonState];
    });

    if (gpg::IsSuccess(status)) {
        NSLog(@"Status: success.");
    } else {
        NSLog(@"Status: failure.");
    }
}

@end
