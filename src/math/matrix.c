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
        return lx_mat2_zero();

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
    return (lx_mat3){
        .m = {
            0.0f
        }
    };
}

lx_mat3 lx_mat3_identity()
{
    return (lx_mat3){
        .m = {
            1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
        }
    };
}

lx_mat3 lx_mat3_from_mat2(lx_mat2 m)
{
    return (lx_mat3){
        .m = {
            m.m[0], m.m[1], 0.0f, m.m[2], m.m[3], 0.0f, 0.0f, 0.0f, 0.0f
        }
    };
}

lx_mat3 lx_mat3_from_mat4(lx_mat4 m)
{
    return (lx_mat3){
        .m = {
            m.m[0], m.m[1], m.m[2], m.m[4], m.m[5], m.m[6], m.m[8], m.m[9], m.m[10]
        }
    };
}

lx_mat3 lx_mat3_add(lx_mat3 a, lx_mat3 b)
{
    lx_mat3 n;

    for (int i = 0; i < 9; i++)
        n.m[i] = a.m[i] + b.m[i];

    return n;
}

lx_mat3 lx_mat3_sub(lx_mat3 a, lx_mat3 b)
{
    lx_mat3 n;

    for (int i = 0; i < 9; i++)
        n.m[i] = a.m[i] - b.m[i];

    return n;
}

lx_mat3 lx_mat3_mul(lx_mat3 a, lx_mat3 b)
{
    return (lx_mat3){
        .m = {
            a.m[0] * b.m[0] + a.m[3] * b.m[1] + a.m[6] * b.m[2],
            a.m[1] * b.m[0] + a.m[4] * b.m[1] + a.m[7] * b.m[2],
            a.m[2] * b.m[0] + a.m[5] * b.m[1] + a.m[8] * b.m[2],
            a.m[0] * b.m[3] + a.m[3] * b.m[4] + a.m[6] * b.m[5],
            a.m[1] * b.m[3] + a.m[4] * b.m[4] + a.m[7] * b.m[5], 
            a.m[2] * b.m[3] + a.m[5] * b.m[4] + a.m[8] * b.m[5], 
            a.m[0] * b.m[6] + a.m[3] * b.m[7] + a.m[6] * b.m[8],
            a.m[1] * b.m[6] + a.m[4] * b.m[7] + a.m[7] * b.m[8], 
            a.m[2] * b.m[6] + a.m[5] * b.m[7] + a.m[8] * b.m[8]
        }
    };
}

lx_mat3 lx_mat3_scale_by_scalar(lx_mat3 a, float scale)
{
    lx_mat3 n;

    for (int i = 0; i < 9; i++)
        n.m[i] = a.m[i] * scale;

    return n;
}

lx_mat3 lx_mat3_transpose(lx_mat3 m)
{
    return (lx_mat3){
        .m = {
            m.m[0], m.m[3], m.m[6], m.m[1], m.m[4], m.m[7], m.m[2], m.m[5], m.m[8]
        }
    };
}

lx_mat3 lx_mat3_inverse(lx_mat3 m)
{
    float a = m.m[0];
    float b = m.m[1];
    float c = m.m[2];
    float d = m.m[3];
    float e = m.m[4];
    float f = m.m[5];
    float g = m.m[6];
    float h = m.m[7];
    float i = m.m[8];

    float A =  (e * i - f * h);
    float B = -(d * i - f * g);
    float C =  (d * h - e * g);
    float D = -(b * i - c * h);
    float E =  (a * i - c * g);
    float F = -(a * h - b * g);
    float G =  (b * f - c * e);
    float H = -(a * f - c * d);
    float I =  (a * e - b * d);

    float det = a * A + b * B + c * C;

    if (det == 0.0f)
        return lx_mat3_zero();

    float inv_det = 1.0f / det;

    return (lx_mat3){
        .m = {
            A * inv_det,
            D * inv_det,
            G * inv_det,
            B * inv_det,
            E * inv_det,
            H * inv_det,
            C * inv_det,
            F * inv_det,
            I * inv_det
        }
    };
}

lx_vec3 lx_mat3_mul_vec3(lx_mat3 m, lx_vec3 v)
{
    return (lx_vec3){
        m.m[0] * v.x + m.m[3] * v.y + m.m[6] * v.z,
        m.m[1] * v.x + m.m[4] * v.y + m.m[7] * v.z,
        m.m[2] * v.x + m.m[5] * v.y + m.m[8] * v.z,
    };
}

int lx_mat3_equal(lx_mat3 a, lx_mat3 b, float epsilon)
{
    for (int i = 0; i < 9; i++)
    {
        if (fabsf(a.m[i] - b.m[i]) > epsilon)
            return 0;
    }

    return 1;
}

lx_mat4 lx_mat4_zero()
{
    return (lx_mat4){
        .m = {
            0.0f
        }
    };
}

lx_mat4 lx_mat4_identity()
{
    return (lx_mat4){
        .m = {
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        }
    };
}

lx_mat4 lx_mat4_from_mat2(lx_mat2 m)
{
    return (lx_mat4){
        .m = {
            m.m[0], m.m[1], 0.0f, 0.0f, m.m[2], m.m[3], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
        }
    };
}

lx_mat4 lx_mat4_from_mat3(lx_mat3 m)
{
    return (lx_mat4){
        .m = {
            m.m[0], m.m[1], m.m[2], 0.0f, m.m[3], m.m[4], m.m[5], 0.0f, m.m[6], m.m[7], m.m[8], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
        }
    };
}

lx_mat4 lx_mat4_add(lx_mat4 a, lx_mat4 b)
{
    lx_mat4 n;

    for (int i = 0; i < 16; i++)
        n.m[i] = a.m[i] + b.m[i];

    return n;
}

lx_mat4 lx_mat4_sub(lx_mat4 a, lx_mat4 b)
{
    lx_mat4 n;

    for (int i = 0; i < 16; i++)
        n.m[i] = a.m[i] - b.m[i];

    return n;
}

lx_mat4 lx_mat4_mul(lx_mat4 a, lx_mat4 b)
{
    return (lx_mat4){
        .m = {
            a.m[0] * b.m[0] + a.m[4] * b.m[1] + a.m[8] * b.m[2] + a.m[12] * b.m[3],
            a.m[1] * b.m[0] + a.m[5] * b.m[1] + a.m[9] * b.m[2] + a.m[13] * b.m[3],
            a.m[2] * b.m[0] + a.m[6] * b.m[1] + a.m[10] * b.m[2] + a.m[14] * b.m[3],
            a.m[3] * b.m[0] + a.m[7] * b.m[1] + a.m[11] * b.m[2] + a.m[15] * b.m[3],
            a.m[0] * b.m[4] + a.m[4] * b.m[5] + a.m[8] * b.m[6]  + a.m[12] * b.m[7],
            a.m[1] * b.m[4] + a.m[5] * b.m[5] + a.m[9] * b.m[6]  + a.m[13] * b.m[7],
            a.m[2] * b.m[4] + a.m[6] * b.m[5] + a.m[10] * b.m[6] + a.m[14] * b.m[7],
            a.m[3] * b.m[4] + a.m[7] * b.m[5] + a.m[11] * b.m[6] + a.m[15] * b.m[7],
            a.m[0] * b.m[8] + a.m[4] * b.m[9] + a.m[8] * b.m[10] + a.m[12] * b.m[11],
            a.m[1] * b.m[8] + a.m[5] * b.m[9] + a.m[9] * b.m[10] + a.m[13] * b.m[11],
            a.m[2] * b.m[8] + a.m[6] * b.m[9] + a.m[10] * b.m[10] + a.m[14] * b.m[11],
            a.m[3] * b.m[8] + a.m[7] * b.m[9] + a.m[11] * b.m[10] + a.m[15] * b.m[11],
            a.m[0] * b.m[12] + a.m[4] * b.m[13] + a.m[8] * b.m[14] + a.m[12] * b.m[15],
            a.m[1] * b.m[12] + a.m[5] * b.m[13] + a.m[9] * b.m[14] + a.m[13] * b.m[15],
            a.m[2] * b.m[12] + a.m[6] * b.m[13] + a.m[10] * b.m[14] + a.m[14] * b.m[15],
            a.m[3] * b.m[12] + a.m[7] * b.m[13] + a.m[11] * b.m[14] + a.m[15] * b.m[15]
        }
    };
}

lx_mat4 lx_mat4_scale_by_scalar(lx_mat4 a, float scale)
{
    lx_mat4 n;

    for (int i = 0; i < 16; i++)
        n.m[i] = a.m[i] * scale;

    return n;
}

lx_mat4 lx_mat4_transpose(lx_mat4 m)
{
    return (lx_mat4){
        .m = {
            m.m[0], m.m[4], m.m[8], m.m[12], m.m[1], m.m[5], m.m[9], m.m[13],
            m.m[2], m.m[6], m.m[10], m.m[14], m.m[3], m.m[7], m.m[11], m.m[15]
        }
    };
}   

lx_mat4 lx_mat4_inverse(lx_mat4 m)
{
    lx_mat4 inv;
    lx_mat4 n;

    inv.m[0] = m.m[5] * m.m[10] * m.m[15] - m.m[5] * m.m[11] * m.m[14] - m.m[9] * m.m[6] * m.m[15] + m.m[9] * m.m[7] * m.m[14] + m.m[13] * m.m[6] * m.m[11] - m.m[13] * m.m[7] * m.m[10];
    inv.m[4] = -m.m[4] * m.m[10] * m.m[15] + m.m[4] * m.m[11] * m.m[14] + m.m[8] * m.m[6] * m.m[15] - m.m[8] * m.m[7] * m.m[14] - m.m[12] * m.m[6] * m.m[11] + m.m[12] * m.m[7] * m.m[10];
    inv.m[8] = m.m[4] * m.m[9] * m.m[15] - m.m[4] * m.m[11] * m.m[13] - m.m[8] * m.m[5] * m.m[15] + m.m[8] * m.m[7] * m.m[13] + m.m[12] * m.m[5] * m.m[11] - m.m[12] * m.m[7] * m.m[9];
    inv.m[12] = -m.m[4] * m.m[9] * m.m[14] + m.m[4] * m.m[10] * m.m[13] +m.m[8] * m.m[5] * m.m[14] - m.m[8] * m.m[6] * m.m[13] - m.m[12] * m.m[5] * m.m[10] + m.m[12] * m.m[6] * m.m[9];
    inv.m[1] = -m.m[1] * m.m[10] * m.m[15] + m.m[1] * m.m[11] * m.m[14] + m.m[9] * m.m[2] * m.m[15] - m.m[9] * m.m[3] * m.m[14] - m.m[13] * m.m[2] * m.m[11] + m.m[13] * m.m[3] * m.m[10];
    inv.m[5] = m.m[0] * m.m[10] * m.m[15] - m.m[0] * m.m[11] * m.m[14] - m.m[8] * m.m[2] * m.m[15] + m.m[8] * m.m[3] * m.m[14] + m.m[12] * m.m[2] * m.m[11] - m.m[12] * m.m[3] * m.m[10];
    inv.m[9] = -m.m[0] * m.m[9] * m.m[15] + m.m[0] * m.m[11] * m.m[13] + m.m[8] * m.m[1] * m.m[15] - m.m[8] * m.m[3] * m.m[13] - m.m[12] * m.m[1] * m.m[11] + m.m[12] * m.m[3] * m.m[9];
    inv.m[13] = m.m[0] * m.m[9] * m.m[14] - m.m[0] * m.m[10] * m.m[13] - m.m[8] * m.m[1] * m.m[14] + m.m[8] * m.m[2] * m.m[13] + m.m[12] * m.m[1] * m.m[10] - m.m[12] * m.m[2] * m.m[9];
    inv.m[2] = m.m[1] * m.m[6] * m.m[15] - m.m[1] * m.m[7] * m.m[14] - m.m[5] * m.m[2] * m.m[15] + m.m[5] * m.m[3] * m.m[14] + m.m[13] * m.m[2] * m.m[7] - m.m[13] * m.m[3] * m.m[6];
    inv.m[6] = -m.m[0] * m.m[6] * m.m[15] + m.m[0] * m.m[7] * m.m[14] + m.m[4] * m.m[2] * m.m[15] - m.m[4] * m.m[3] * m.m[14] - m.m[12] * m.m[2] * m.m[7] + m.m[12] * m.m[3] * m.m[6];
    inv.m[10] = m.m[0] * m.m[5] * m.m[15] - m.m[0] * m.m[7] * m.m[13] - m.m[4] * m.m[1] * m.m[15] + m.m[4] * m.m[3] * m.m[13] + m.m[12] * m.m[1] * m.m[7] - m.m[12] * m.m[3] * m.m[5];
    inv.m[14] = -m.m[0] * m.m[5] * m.m[14] + m.m[0] * m.m[6] * m.m[13] + m.m[4] * m.m[1] * m.m[14] - m.m[4] * m.m[2] * m.m[13] - m.m[12] * m.m[1] * m.m[6] + m.m[12] * m.m[2] * m.m[5];
    inv.m[3] = -m.m[1] * m.m[6] * m.m[11] + m.m[1] * m.m[7] * m.m[10] + m.m[5] * m.m[2] * m.m[11] - m.m[5] * m.m[3] * m.m[10] - m.m[9] * m.m[2] * m.m[7] + m.m[9] * m.m[3] * m.m[6];
    inv.m[7] = m.m[0] * m.m[6] * m.m[11] - m.m[0] * m.m[7] * m.m[10] - m.m[4] * m.m[2] * m.m[11] + m.m[4] * m.m[3] * m.m[10] + m.m[8] * m.m[2] * m.m[7] - m.m[8] * m.m[3] * m.m[6];
    inv.m[11] = -m.m[0] * m.m[5] * m.m[11] + m.m[0] * m.m[7] * m.m[9] + m.m[4] * m.m[1] * m.m[11] - m.m[4] * m.m[3] * m.m[9] - m.m[8] * m.m[1] * m.m[7] + m.m[8] * m.m[3] * m.m[5];
    inv.m[15] = m.m[0] * m.m[5] * m.m[10] - m.m[0] * m.m[6] * m.m[9] - m.m[4] * m.m[1] * m.m[10] + m.m[4] * m.m[2] * m.m[9] + m.m[8] * m.m[1] * m.m[6] - m.m[8] * m.m[2] * m.m[5];

    float det = m.m[0] * inv.m[0] + m.m[1] * inv.m[4] + m.m[2] * inv.m[8] + m.m[3] * inv.m[12];

    if (det == 0.0f)
        return lx_mat4_zero();

    det = 1.0f / det;
 
    for (int i = 0; i < 16; i++)
        n.m[i] = inv.m[i] * det;

    return n;
}

lx_mat4 lx_mat4_translate(lx_mat4 m, lx_vec3 translation)
{
    lx_mat4 t = {
        .m = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            translation.x, translation.y, translation.z, 1.0f
        }
    };

    return lx_mat4_mul(m, t);
}

lx_mat4 lx_mat4_scale(lx_mat4 m, lx_vec3 scale)
{
    lx_mat4 s = {
        .m = {
            scale.x, 0.0f, 0.0f, 0.0f,
            0.0f, scale.y, 0.0f, 0.0f,
            0.0f, 0.0f, scale.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }
    };

    return lx_mat4_mul(m, s);
}

lx_mat4 lx_mat4_rotate(lx_mat4 m, lx_vec3 axis, float degrees)
{
    axis = lx_vec3_normalize(axis);
    float rad = lx_deg_to_rad(degrees);
    float c = cosf(rad);
    float s = sinf(rad);
    float one_c = 1.0f - c;

    lx_mat4 r = {
        .m = {
            c + one_c * axis.x * axis.x,
            one_c * axis.x * axis.y + s * axis.z,
            one_c * axis.x * axis.z - s * axis.y,
            0.0f,

            one_c * axis.x * axis.y - s * axis.z,
            c + one_c * axis.y * axis.y,
            one_c * axis.y * axis.z + s * axis.x,
            0.0f,

            one_c * axis.x * axis.z + s * axis.y,
            one_c * axis.y * axis.z - s * axis.x,
            c + one_c * axis.z * axis.z,
            0.0f,

            0.0f, 0.0f, 0.0f, 1.0f
        }
    };

    return lx_mat4_mul(m, r);
}

lx_mat4 lx_mat4_look_at(lx_vec3 eye, lx_vec3 center, lx_vec3 up)
{
    lx_vec3 f = lx_vec3_normalize(lx_vec3_sub(center, eye));
    lx_vec3 s = lx_vec3_normalize(lx_vec3_cross(f, up));
    lx_vec3 u = lx_vec3_cross(s, f);

    float tx = -lx_vec3_dot(s, eye);
    float ty = -lx_vec3_dot(u, eye);
    float tz =  lx_vec3_dot(f, eye);

    lx_mat4 view = {
        .m = {
            s.x, u.x, -f.x, 0.0f,
            s.y, u.y, -f.y, 0.0f,
            s.z, u.z, -f.z, 0.0f,
            tx,  ty,   tz,  1.0f
        }
    };

    return view;
}

lx_mat4 lx_mat4_perspective(float fov, float aspect, float near, float far)
{
    float f = 1.0f / tanf(lx_deg_to_rad(fov) * 0.5f);
    float nf = 1.0f / (near - far);

    lx_mat4 m = {
        .m = {
            f / aspect, 0.0f, 0.0f, 0.0f,
            0.0f, f, 0.0f, 0.0f,
            0.0f, 0.0f, (far + near) * nf, -1.0f,
            0.0f, 0.0f, (2.0f * far * near) * nf, 0.0f
        }
    };

    return m;
}

lx_mat4 lx_mat4_orthographic(float left, float right, float bottom, float top, float near, float far)
{
    float lr = 1.0f / (left - right);
    float bt = 1.0f / (bottom - top);
    float nf = 1.0f / (near - far);

    lx_mat4 m = {
        .m = {
            -2.0f * lr, 0.0f, 0.0f, 0.0f,
             0.0f, -2.0f * bt, 0.0f, 0.0f,
             0.0f, 0.0f, 2.0f * nf, 0.0f,
            (left + right) * lr, (top + bottom) * bt, (far + near) * nf, 1.0f
        }
    };

    return m;
}

lx_vec4 lx_mat4_mul_vec4(lx_mat4 m, lx_vec4 v)
{
    return (lx_vec4){
        m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12] * v.w,
        m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13] * v.w,
        m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14] * v.w,
        m.m[3] * v.x + m.m[7] * v.y + m.m[11] * v.z + m.m[15] * v.w,
    };
}

int lx_mat4_equal(lx_mat4 a, lx_mat4 b, float epsilon)
{
    for (int i = 0; i < 16; i++)
    {
        if (fabsf(a.m[i] - b.m[i]) > epsilon)
            return 0;
    }

    return 1;
}

