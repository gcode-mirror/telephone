//
//  AKCallController.h
//  Telephone
//
//  Copyright (c) 2008-2009 Alexei Kuznetsov. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. The name of the author may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY ALEXEI KUZNETSOV "AS IS" AND ANY EXPRESS
//  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
//  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <Cocoa/Cocoa.h>

#import "AKActiveCallView.h"


@class AKAccountController, AKTelephoneCall;

@interface AKCallController : NSWindowController <AKActiveCallViewDelegate> {
@private
  NSString *identifier;
  AKTelephoneCall *call;
  AKAccountController *accountController;
  NSString *displayedName;
  NSString *status;
  NSString *nameFromAddressBook;
  NSString *phoneLabelFromAddressBook;
  NSString *enteredCallDestination;
  NSTimer *intermediateStatusTimer;
  NSTimeInterval callStartTime;
  NSTimer *callTimer;
  BOOL callOnHold;
  NSMutableString *enteredDTMF;
  
  NSView *incomingCallView;
  NSView *activeCallView;
  NSView *endedCallView;
  NSButton *hangUpButton;
  NSButton *acceptCallButton;
  NSButton *declineCallButton;
  NSTextField *displayedNameField;
  NSTextField *endedCallDisplayedNameField;
  NSTextField *statusField;
  NSProgressIndicator *callProgressIndicator;
}

@property(readwrite, copy) NSString *identifier;
@property(readwrite, retain) AKTelephoneCall *call;
@property(nonatomic, readwrite, assign) AKAccountController *accountController;
@property(readwrite, copy) NSString *displayedName;
@property(readwrite, copy) NSString *status;
@property(readwrite, copy) NSString *nameFromAddressBook;
@property(readwrite, copy) NSString *phoneLabelFromAddressBook;
@property(readwrite, copy) NSString *enteredCallDestination;
@property(readwrite, retain) NSTimer *intermediateStatusTimer;
@property(readwrite, assign) NSTimeInterval callStartTime;
@property(readwrite, retain) NSTimer *callTimer;
@property(readwrite, assign) BOOL callOnHold;
@property(readwrite, retain) NSMutableString *enteredDTMF;

@property(nonatomic, retain) IBOutlet NSView *incomingCallView;
@property(nonatomic, retain) IBOutlet NSView *activeCallView;
@property(nonatomic, retain) IBOutlet NSView *endedCallView;
@property(nonatomic, retain) IBOutlet NSButton *hangUpButton;
@property(nonatomic, retain) IBOutlet NSButton *acceptCallButton;
@property(nonatomic, retain) IBOutlet NSButton *declineCallButton;
@property(nonatomic, retain) IBOutlet NSTextField *displayedNameField;
@property(nonatomic, retain) IBOutlet NSTextField *endedCallDisplayedNameField;
@property(nonatomic, retain) IBOutlet NSTextField *statusField;
@property(nonatomic, retain) IBOutlet NSProgressIndicator *callProgressIndicator;

// Designated initializer
- (id)initWithAccountController:(AKAccountController *)anAccountController;

- (IBAction)acceptCall:(id)sender;
- (IBAction)hangUpCall:(id)sender;

- (IBAction)toggleCallHold:(id)sender;
- (IBAction)toggleMicrophoneMute:(id)sender;

// Force ended call state not waiting for the callbacks. This is useful with
// AKTelephone's hangUpAllCalls when computer goes to sleep or before app
// shuts down.
- (void)forceEndedCallState;

// Dealing with the timer of active call.
- (void)startCallTimer;
- (void)stopCallTimer;
- (void)callTimerTick:(NSTimer *)theTimer;

- (void)setIntermediateStatus:(NSString *)newIntermediateStatus;
- (void)intermediateStatusTimerTick:(NSTimer *)theTimer;

@end


// Notifications.
// accountController will be subscribed to this notification in its setter.
extern NSString * const AKTelephoneCallWindowWillCloseNotification;
