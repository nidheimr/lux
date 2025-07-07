#include "lux/math.h"

#include <math.h>

//
//  private
//

static const float PI = 3.14159265358979323846;

//
//  public
//

float lx_clampf(float f, float min, float max)
{
    if (f < min) return min;
    if (f > max) return max;
    return f;
}

float lx_lerpf(float a, float b, float t)
{
    return a + (b - a) * t;
}

float lx_deg_to_rad(float degrees)
{
    return degrees * (PI / 180); 
}

float lx_rad_to_deg(float radians)
{
    return radians * (180 / PI);
}

int lx_float_equal(float a, float b, float epsilon)
{
    return fabsf(a - b) <= epsilon;
}
