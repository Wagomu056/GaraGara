//
// Created by 東口拓也 on 2022/06/20.
//

#ifndef BOUND_BALL_MATH_UTIL_H
#define BOUND_BALL_MATH_UTIL_H

#include "vec2.h"

void rotateVec2(const struct Vec2 *vec, float rad, struct Vec2 *out);
float degreeToRadian(float degree);
float clamp(float value, float min, float max);
int clampI(int value, int min, int max);
float linear(float value1, float value2, float ratio);
float easeInOut(float ts);

#endif //BOUND_BALL_MATH_UTIL_H
