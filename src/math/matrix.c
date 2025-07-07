#include "lux/math.h"

#include <math.h>

//
//  public
//

lx_mat2 lx_mat2_zero()
{
    return (lx_mat2){
        .m = {
            0.0f
        }
    };
}

lx_mat2 lx_mat2_identity()
{
    return (lx_mat2){
        .m = {
            1.0f, 0.0f, 0.0f, 1.0f
        }
    };
}

lx_mat2 lx_mat2_from_mat3(lx_mat3 m)
{
    return (lx_mat2){
        .m = {
            m.m[0], m.m[1], m.m[3], m.m[4]
        }
    };
}

lx_mat2 lx_mat2_from_mat4(lx_mat4 m)
{
    return (lx_mat2){
        .m = {
            m.m[0], m.m[1], m.m[4], m.m[5]
        }
    };
}

lx_mat2 lx_mat2_add(lx_mat2 a, lx_mat2 b)
{
    lx_mat2 n;

    for (int i = 0; i < 4; i++)
        n.m[i] = a.m[i] + b.m[i];

    return n;
}

lx_mat2 lx_mat2_sub(lx_mat2 a, lx_mat2 b)
{
    lx_mat2 n;

    for (int i = 0; i < 4; i++)
        n.m[i] = a.m[i] - b.m[i];

    return n;
}

lx_mat2 lx_mat2_mul(lx_mat2 a, lx_mat2 b)
{
    return (lx_mat2){
        a.m[0] * b.m[0] + a.m[2] * b.m[1],
        a.m[1] * b.m[0] + a.m[3] * b.m[1],
        a.m[0] * b.m[2] + a.m[2] * b.m[3],
        a.m[1] * b.m[2] + a.m[3] * b.m[3]
    };
}

lx_mat2 lx_mat2_scale_by_scalar(lx_mat2 a, float scale)
{
    lx_mat2 n;

    for (int i = 0; i < 4; i++)
        n.m[i] = a.m[i] * scale;

    return n;
}

lx_mat2 lx_mat2_transpose(lx_mat2 m)
{
    return (lx_mat2){
        .m = {
            m.m[0], m.m[2], m.m[1], m.m[3]
        }
    };
}

lx_mat2 lx_mat2_inverse(lx_mat2 m)
{
    float a = m.m[0];
    float b = m.m[2];
    float c = m.m[1];
    float d = m.m[3];

    float det = a * d - b * c;

    if (det == 0.0f)
        return lx_mat2_identity();

    float inv_det = 1.0f / det;

    return (lx_mat2){
        .m = {
            d * inv_det,
            -c * inv_det,
            -b * inv_det,
            a * inv_det
        }
    };
}

lx_vec2 lx_mat2_mul_vec2(lx_mat2 m, lx_vec2 v)
{
    return (lx_vec2){
        m.m[0] * v.x + m.m[2] * v.y,
        m.m[1] * v.x + m.m[3] * v.y
    };
}

int lx_mat2_equal(lx_mat2 a, lx_mat2 b, float epsilon)
{
    for (int i = 0; i < 4; i++)
    {
        if (fabsf(a.m[i] - b.m[i]) > epsilon)
            return 0;
    }

    return 1;
}

lx_mat3 lx_mat3_zero()
{
}

lx_mat3 lx_mat3_identity()
{
}
o
lx_mat3 lx_mat3_from_mat2(lx_mat2 m)
{
}

lx_mat3 lx_mat3_from_mat4(lx_mat4 m)
{
}

lx_mat3 lx_mat3_add(lx_mat3 a, lx_mat3 b)
{
}

lx_mat3 lx_mat3_sub(lx_mat3 a, lx_mat3 b)
{
}

lx_mat3 lx_mat3_mul(lx_mat3 a, lx_mat3 b)
{
}

lx_mat3 lx_mat3_scale_by_scalar(lx_mat3 a, float scale)
{
}

lx_mat3 lx_mat3_transpose(lx_mat3 m)
{
}

lx_mat3 lx_mat3_inverse(lx_mat3 m)
{
}

lx_vec3 lx_mat3_mul_vec3(lx_mat3 m, lx_vec3 v)
{
}

int lx_mat3_equal(lx_mat3 a, lx_mat3 b, float epsilon)
{
}

lx_mat4 lx_mat4_zero()
{
}

lx_mat4 lx_mat4_identity()
{
}

lx_mat4 lx_mat4_from_mat2(lx_mat2 m)
{
}

lx_mat4 lx_mat4_from_mat3(lx_mat3 m)
{
}

lx_mat4 lx_mat4_add(lx_mat4 a, lx_mat4 b)
{
}

lx_mat4 lx_mat4_sub(lx_mat4 a, lx_mat4 b)
{
}

lx_mat4 lx_mat4_mul(lx_mat4 a, lx_mat4 b)
{
}

lx_mat4 lx_mat4_scale_by_scalar(lx_mat4 a, float scale)
{
}

lx_mat4 lx_mat4_transpose(lx_mat4 m)
{
}

lx_mat4 lx_mat4_inverse(lx_mat4 m)
{
}

lx_mat4 lx_mat4_translate(lx_mat4 m, lx_vec3 translation)
{
}

lx_mat4 lx_mat4_scale(lx_mat4 m, lx_vec3 scale)
{
}

lx_mat4 lx_mat4_rotate_axis_angle(lx_mat4 m, lx_vec3 axis, float degrees)
{
}

lx_mat4 lx_mat4_rotate_euler(lx_mat4 m, float pitch, float yaw, float roll)
{
}

lx_mat4 lx_mat4_look_at(lx_vec3 eye, lx_vec3 center, lx_vec3 up)
{
}

lx_mat4 lx_mat4_perspective(float fov, float aspect, float near, float far)
{
}

lx_mat4 lx_mat4_orthographic(float left, float right, float bottom, float top, float near, float far)
{
}

lx_vec4 lx_mat4_mul_vec4(lx_mat4 m, lx_vec4 v)
{
}

int lx_mat4_equal(lx_mat4 a, lx_mat4 b, float epsilon)
{
}

