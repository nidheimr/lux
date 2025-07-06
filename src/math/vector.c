#include "lux/math.h"

#include <math.h>

lx_vec2 lx_vec2_zero()
{
    return (lx_vec2){ 0.0f };
}

lx_vec2 lx_vec2_from_vec3(lx_vec3 v)
{
    return (lx_vec2){
        v.x,
        v.y
    };
}

lx_vec2 lx_vec2_from_vec4(lx_vec4 v)
{
    return (lx_vec2){
        v.x,
        v.y
    };
}

lx_vec2 lx_vec2_add(lx_vec2 a, lx_vec2 b)
{
    return (lx_vec2){
        a.x + b.x,
        a.y + b.y
    };
}

lx_vec2 lx_vec2_sub(lx_vec2 a, lx_vec2 b)
{
    return (lx_vec2){
        a.x - b.x,
        a.y - b.y
    };
}

lx_vec2 lx_vec2_mul(lx_vec2 a, lx_vec2 b)
{
    return (lx_vec2){
        a.x * b.x,
        a.y * b.y
    };
}

lx_vec2 lx_vec2_scale_by_scalar(lx_vec2 v, float scale)
{
    return (lx_vec2){
        v.x * scale,
        v.y * scale
    };
}

lx_vec2 lx_vec2_normalize(lx_vec2 v)
{
    float mag = lx_vec2_magnitude(v);
    
    if (mag == 0.0f)
        return (lx_vec2){ 0.0f };

    return (lx_vec2){
        v.x / mag,
        v.y / mag
    };
}

lx_vec2 lx_vec2_lerp(lx_vec2 a, lx_vec2 b, float t)
{
    return (lx_vec2){
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t
    };
}

lx_vec2 lx_vec2_clamp(lx_vec2 v, lx_vec2 min, lx_vec2 max)
{
    return (lx_vec2){
        lx_clampf(v.x, min.x, max.x),
        lx_clampf(v.y, min.y, max.y)
    };
}

float lx_vec2_dot(lx_vec2 a, lx_vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

float lx_vec2_magnitude(lx_vec2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

float lx_vec2_magnitude_squared(lx_vec2 v)
{
    return v.x * v.x + v.y * v.y;
}

int lx_vec2_equal(lx_vec2 a, lx_vec2 b, float epsilon)
{
    return (fabsf(a.x - b.x) <= epsilon) &&
            (fabsf(a.y - b.y) <= epsilon);
}

lx_vec3 lx_vec3_zero()
{
    return (lx_vec3){ 0.0f };
}

lx_vec3 lx_vec3_from_vec2(lx_vec2 v)
{
    return (lx_vec3){
        v.x,
        v.y,
        0.0f
    };
}

lx_vec3 lx_vec3_from_vec4(lx_vec4 v)
{
    return (lx_vec3){
        v.x,
        v.y,
        v.z
    };
}

lx_vec3 lx_vec3_add(lx_vec3 a, lx_vec3 b)
{
    return (lx_vec3){
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

lx_vec3 lx_vec3_sub(lx_vec3 a, lx_vec3 b)
{
    return (lx_vec3){
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

lx_vec3 lx_vec3_mul(lx_vec3 a, lx_vec3 b)
{
    return (lx_vec3){
        a.x * b.x,
        a.y * b.y,
        a.z * b.z
    };
}

lx_vec3 lx_vec3_scale_by_scalar(lx_vec3 v, float scale)
{
    return (lx_vec3){
        v.x * scale,
        v.y * scale,
        v.z * scale 
    };
}

lx_vec3 lx_vec3_normalize(lx_vec3 v)
{
    float mag = lx_vec3_magnitude(v);
    
    if (mag == 0.0f)
        return (lx_vec3){ 0.0f };

    return (lx_vec3){
        v.x / mag,
        v.y / mag,
        v.z / mag
    };
}

lx_vec3 lx_vec3_lerp(lx_vec3 a, lx_vec3 b, float t)
{
    return (lx_vec3){
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t
    };
}

lx_vec3 lx_vec3_clamp(lx_vec3 v, lx_vec3 min, lx_vec3 max)
{
    return (lx_vec3){
        lx_clampf(v.x, min.x, max.x),
        lx_clampf(v.y, min.y, max.y),
        lx_clampf(v.z, min.z, max.z)
    };
}

lx_vec3 lx_vec3_reflect(lx_vec3 i, lx_vec3 n)
{
    float dot = lx_vec3_dot(i,n);
    lx_vec3 scaled = lx_vec3_scale_by_scalar(n, 2.0f * dot);

    return lx_vec3_sub(i, scaled);
}

float lx_vec3_dot(lx_vec3 a, lx_vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float lx_vec3_magnitude(lx_vec3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float lx_vec3_magnitude_squared(lx_vec3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float lx_vec3_distance(lx_vec3 a, lx_vec3 b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;

    return sqrtf(dx * dx + dy * dy + dz * dz);
}

int lx_vec3_equal(lx_vec3 a, lx_vec3 b, float epsilon)
{
    return (fabsf(a.x - b.x) <= epsilon) &&
            (fabsf(a.y - b.y) <= epsilon) &&
            (fabsf(a.z - b.z) <= epsilon);
}

lx_vec3 lx_vec3_cross(lx_vec3 a, lx_vec3 b)
{
    return (lx_vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

lx_vec4 lx_vec4_zero()
{
    return (lx_vec4){ 0.0f };
}

lx_vec4 lx_vec4_from_vec2(lx_vec2 v)
{
    return (lx_vec4){
        v.x,
        v.y,
        0.0f,
        0.0f
    };
}

lx_vec4 lx_vec4_from_vec3(lx_vec3 v)
{
    return (lx_vec4){
        v.x,
        v.y,
        v.z,
        0.0f
    };
}

lx_vec4 lx_vec4_add(lx_vec4 a, lx_vec4 b)
{
    return (lx_vec4){
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    };
}

lx_vec4 lx_vec4_sub(lx_vec4 a, lx_vec4 b)
{
    return (lx_vec4){
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    };
}

lx_vec4 lx_vec4_mul(lx_vec4 a, lx_vec4 b)
{
    return (lx_vec4){
        a.x * b.x,
        a.y * b.y,
        a.z * b.z,
        a.w * b.w
    };
}

lx_vec4 lx_vec4_scale_by_scalar(lx_vec4 v, float scale)
{
    return (lx_vec4){
        v.x * scale,
        v.y * scale,
        v.z * scale,
        v.w * scale
    };
}

lx_vec4 lx_vec4_normalize(lx_vec4 v)
{
    float mag = lx_vec4_magnitude(v);

    if (mag == 0.0f)
        return (lx_vec4){ 0.0f };

    return (lx_vec4){
        v.x / mag,
        v.y / mag,
        v.z / mag,
        v.w / mag
    };
}

lx_vec4 lx_vec4_lerp(lx_vec4 a, lx_vec4 b, float t)
{
    return (lx_vec4){
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t,
        a.w + (b.w - a.w) * t
    };
}

lx_vec4 lx_vec4_clamp(lx_vec4 v, lx_vec4 min, lx_vec4 max)
{
    return (lx_vec4){
        lx_clampf(v.x, min.x, max.x),
        lx_clampf(v.y, min.y, max.y),
        lx_clampf(v.z, min.z, max.z),
        lx_clampf(v.w, min.w, max.w)
    };
}

float lx_vec4_dot(lx_vec4 a, lx_vec4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float lx_vec4_magnitude(lx_vec4 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float lx_vec4_magnitude_squared(lx_vec4 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

int lx_vec4_equal(lx_vec4 a, lx_vec4 b, float epsilon)
{
    return fabsf(a.x - b.x) <= epsilon &&
            fabsf(a.y - b.y) <= epsilon &&
            fabsf(a.z - b.z) <= epsilon &&
            fabsf(a.w - b.w) <= epsilon;
}
