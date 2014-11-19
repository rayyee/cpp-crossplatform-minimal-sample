//
//  ViewController.h
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

#import <UIKit/UIKit.h>
#import "StateManager.h"
#import "GLDrawer.h"

#import <GLKit/GLKit.h>

@interface ViewController : UIViewController <GLKViewDelegate, GLKViewControllerDelegate>

@property (weak, nonatomic) IBOutlet UIButton *signInButton;
@property (weak, nonatomic) IBOutlet UIButton *signOutButton;
@property (weak, nonatomic) IBOutlet UIButton *showAchievementsButton;
@property (weak, nonatomic) IBOutlet UIButton *showLeaderboardsButton;
@property (weak, nonatomic) IBOutlet GLKView *glkView;

@end

