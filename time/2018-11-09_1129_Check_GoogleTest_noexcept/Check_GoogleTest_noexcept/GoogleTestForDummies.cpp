// GoogleTestForDummies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include <iostream>
#include  "MockTurtle.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Painter.h"

using ::testing::AtLeast;               
using ::testing::Exactly;               
using ::testing::Return;
using ::testing::_;

TEST(PainterTest, CanDrawSomething) {
    MockTurtle turtle;                         
    EXPECT_CALL(turtle, PenDown())             
        .Times(Exactly(8));

    Painter painter(&turtle);                  

    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}                                          

