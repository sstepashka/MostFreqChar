//
//  MostFreqCharTests.m
//  MostFreqCharTests
//
//  Created by Kuragin Dmitriy on 02/05/16.
//  Copyright © 2016 Kuragin Dmitriy. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "MostFrequentCharacter.h"

@interface MostFreqCharTests : XCTestCase

@end

@implementation MostFreqCharTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {    
    NSURL *txtURL =  [[NSBundle bundleForClass:[self class]] URLForResource:@"str" withExtension:@"txt"];
    NSString *text = [NSString stringWithContentsOfURL:txtURL encoding:NSUTF8StringEncoding error:nil];
    
    const char* hello = [text cStringUsingEncoding:NSUTF8StringEncoding];
    [self measureBlock:^{
        for (int i = 0; i < 1000; i++) {
            goodMostFrequentCharacter(hello, strlen(hello));
        }
    }];
}

@end
