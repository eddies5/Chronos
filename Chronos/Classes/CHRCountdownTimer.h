//
//  CHRCountdownTimer.h
//  Chronos
//
//  Created by Eduardo Saenz on 4/18/15.
//  Copyright (c) 2015 Comyar Zaheri. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to
//  deal in the Software without restriction, including without limitation the
//  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//  sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//  IN THE SOFTWARE.
//


@import Foundation;
#import "CHRTimer.h"
#import <libkern/OSAtomic.h>


#pragma mark - Forward Declarations

@class CHRCountdownTimer;


#pragma mark - Type Definitions

/**
 The block to execute when the timer reaches zero.
 
 @param     timer
 The timer that fired.
 @param     invocation
 The current invocation number. The first invocation is 0.
 */
typedef void (^CHRCountdownTimerExecutionBlock)(__weak CHRCountdownTimer *timer, NSUInteger invocation);


#pragma mark - CHRDispatchTimer Interface

/**
 The CHRCountdownTimer fires when time reaches zero, but time can be added or
 subtracted. The CHRCountdownTimer is meant to be used once. If subtracting
 time causes the timer's time to become negative, the execution block will fire
 immediately.
 
 A timer has limited accuracy when determining the exact moment to fire; the
 actual time at which a timer fires can potentially be a significant period of
 time after the scheduled firing time.
 */
@interface CHRCountdownTimer : NSObject <CHRTimer>

- (instancetype)init NS_UNAVAILABLE;

// -----
// @name Creating a Countdown Timer
// -----

#pragma mark Creating a Countdown Timer

/**
 Initializes a CHRCountdownTimer object.
 
 The execution block will be executed on the default execution queue.
 
 @param     startTime
 The inital timer time, in seconds.
 @param     executionBlock
 The block to execute when time reaches zero.
 @return    The newly initialized CHRCountdownTimer object.
 */
- (instancetype)initWithStartTime:(NSTimeInterval)startTime
                  executionBlock:(CHRCountdownTimerExecutionBlock)executionBlock;

/**
 Initializes a CHRCountdownTimer object.
 
 @param     startTime
 The inital timer time, in seconds.
 @param     executionBlock
 The block to execute when time reaches zero.
 @param     executionQueue
 The queue that should execute the executionBlock.
 @return    The newly initialized CHRCountdownTimer object.
 */
- (instancetype)initWithStartTime:(NSTimeInterval)startTime
                  executionBlock:(CHRCountdownTimerExecutionBlock)executionBlock
                  executionQueue:(dispatch_queue_t)executionQueue;

/**
 Initializes a CHRCountdownTimer object.
 
 @param     startTime
 The inital timer time, in seconds.
 @param     executionBlock
 The block to execute when time reaches zero.
 @param     executionQueue
 The queue that should execute the executionBlock.
 @param     failureBlock
 The block to execute if the timer fails to initialize.
 @return    The newly initialized CHRCountdownTimer object.
 */
- (instancetype)initWithStartTime:(NSTimeInterval)startTime
                   executionBlock:(CHRCountdownTimerExecutionBlock)executionBlock
                   executionQueue:(dispatch_queue_t)executionQueue
                     failureBlock:(CHRTimerInitFailureBlock)failureBlock
                        NS_DESIGNATED_INITIALIZER;

/**
 Creates a CHRCountdownTimer object.
 
 The execution block will be executed on the default execution queue.
 
 @param     startTime
 The inital timer time, in seconds.
 @param     executinoBlock
 The block to execute when time reaches zero.
 */
+ (CHRCountdownTimer *)countdownTimerWithStartTime:(NSTimeInterval)startTime
                                    executionBlock:(CHRCountdownTimerExecutionBlock)executionBlock;

/**
 Creates a CHRCountdownTimer object.
 
 @param     startTime
 The inital timer time, in seconds.
 @param     executionBlock
 The block to execute when time reaches zero.
 @param     executionQueue
 The queue that should execute the executionBlock.
 @return    The newly initialized CHRCountdownTimer object.
 */
+ (CHRCountdownTimer *)countdownTimerWithStartTime:(NSTimeInterval)startTime
                                    executionBlock:(CHRCountdownTimerExecutionBlock)executionBlock
                                    executionQueue:(dispatch_queue_t)executionQueue;

/**
 Creates a CHRCountdownTimer object.
 
 @param     startTime
 The inital timer time, in seconds.
 @param     executionBlock
 The block to execute when time reaches zero.
 @param     executionQueue
 The queue that should execute the executionBlock.
 @param     failureBlock
 The block to execute if the timer fails to initialize.
 @return    The newly initialized CHRCountdownTimer object.
 */
+ (CHRCountdownTimer *)countdownTimerWithStartTime:(NSTimeInterval)startTime
                                    executionBlock:(CHRCountdownTimerExecutionBlock)executionBlock
                                    executionQueue:(dispatch_queue_t)executionQueue
                                      failureBlock:(CHRTimerInitFailureBlock)failureBlock;

// -----
// @name Using a countdown timer.
// -----

#pragma mark Using a countdown timer.

/**
 Adds time to the CHRCountdownTimer object.
 
 @param     time
 The time to add, in seconds.
 */
- (void)addTime:(NSTimeInterval)time;

/**
 Subtracts time from the CHRCountdownTimer object. If subtracting time causes
 the timer's time to go negative, the execution block will fire immediately.
 
 @param     time
 The time to subtract, in seconds.
 */
- (void)subtractTime:(NSTimeInterval)time;

/**
 Ends the CHRCountdownTimer object and fires the execution block.
 */
- (void)end;

@end
