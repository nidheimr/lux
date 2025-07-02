#include "lux/math.h"

#include <math.h>

float lx_clampf(float f, float min, float max)
{
    if (f < min) return min;
    if (f > max) return max;
    return f;
}

float lx_lerpf(float a, float b, float t)
{
    return a + t * (b - a);
}

float lx_deg_to_rad(float degrees)
{
    const float conversion_factor = 0.01745329251994329576923690768489f;
    return degrees * conversion_factor;
}

float lx_rad_to_deg(float radians)
{
    const float conversion_factor = 57.295779513082320876798154814105f;
    return radians * conversion_factor;
}

int lx_float_equal(float a, float b, float epsilon)
{
    return fabsf(a - b) <= epsilon;
}
