//
// Created by 東口拓也 on 2022/06/20.
//
#include <cmath>
#include "gtest/gtest.h"

extern "C" {
#include <math_util.h>
}

bool equalf(float a, float b)
{
   return (fabs(a - b) <= 0.01f);
}

TEST(Math, rotate) {
    struct Vec2 vec = {1.0f, 0.0f};
    struct Vec2 out = {0.0f, 0.0f};

    rotateVec2(&vec, M_PI_2, &out);
    EXPECT_NEAR(out.x, 0.0f, 0.001f);
    EXPECT_NEAR(out.y, 1.0f, 0.001f);

    rotateVec2(&vec, M_PI, &out);
    EXPECT_NEAR(out.x, -1.0f, 0.001f);
    EXPECT_NEAR(out.y, 0.0f, 0.001f);

    rotateVec2(&vec, M_PI_4, &out);
    EXPECT_NEAR(out.x, 0.707f, 0.001f);
    EXPECT_NEAR(out.y, 0.707f, 0.001f);
}

TEST(Math, degToRad)
{
    float rad = degreeToRadian( 90.0f );
    EXPECT_NEAR(rad, 1.57079632679f, 0.001f);
}

TEST(Math, linear)
{
    float zero = linear(0.0f, 5.0f, 0.0f);
    EXPECT_NEAR(zero, 0.0f, 0.001f);

    float five = linear(0.0f, 5.0f, 1.0f);
    EXPECT_NEAR(five, 5.0f, 0.001f);

    float half = linear(0.0f, 5.0f, 0.5f);
    EXPECT_NEAR(half, 2.5f, 0.001f);
}

TEST(Math, easeInOut)
{
    float zero = easeInOut(0.0f);
    EXPECT_NEAR(zero, 0.0f, 0.001f);

    float one = easeInOut(1.0f);
    EXPECT_NEAR(one, 1.0f, 0.001f);

    float v = easeInOut(0.8f);
    EXPECT_NEAR(v, 0.896, 0.001f);

    float v2 = easeInOut(0.1f);
    EXPECT_NEAR(v2, 0.028f, 0.001f);
}
