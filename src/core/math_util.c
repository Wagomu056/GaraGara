//
// Created by 東口拓也 on 2022/06/20.
//

#include <math.h>
#include "include/math_util.h"

#define M_PIF 3.141592653589793238462643383279502884e+00F

void rotateVec2(const struct Vec2 *vec, float rad, struct Vec2 *out)
{
    const float sin = sinf(rad);
    const float cos = cosf(rad);

    const float x = vec->x;
    const float y = vec->y;
    out->x = x * cos - y * sin;
    out->y = x * sin + y * cos;
}

float degreeToRadian(float degree)
{
    return degree * (M_PIF / 180.0f);
}

float clamp(float value, float min, float max)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

int clampI(int value, int min, int max)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

float linear(float value1, float value2, float ratio)
{
    ratio = clamp(ratio, 0.0f, 1.0f);
    const float d = value2 - value1;
    return value1 + d * ratio;
}

float easeInOut(float ts)
{
    return -2.0f * ts * ts * ts + 3.0f * ts * ts;
}