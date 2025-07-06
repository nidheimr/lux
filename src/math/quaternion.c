#include "lux/math.h"

lx_quat lx_quat_zero()
{

}

lx_quat lx_quat_identity()
{

}

lx_quat lx_quat_from_axis_angle(lx_vec3 axis, float angle)
{

}

lx_quat lx_quat_from_euler(float pitch, float yaw, float roll)
{

}

lx_quat lx_quat_from_mat3(lx_mat3 m)
{

}

lx_quat lx_quat_from_mat4(lx_mat4 m)
{

}

lx_mat3 lx_quat_to_mat3(lx_quat q)
{

}

lx_mat4 lx_quat_to_mat4(lx_quat q)
{

}

lx_vec3 lx_quat_to_euler(lx_quat q)
{

}

lx_quat lx_quat4_conjugate(lx_quat q)
{

}

lx_quat lx_quat4_inverse(lx_quat q)
{

}

lx_quat lx_quat4_normalize(lx_quat q)
{

}

float lx_quat4_magnitude(lx_quat q)
{

}

float lx_quat4_dot(lx_quat a, lx_quat b)
{

}

lx_quat lx_quat4_lerp(lx_quat a, lx_quat b, float t)
{

}

lx_quat lx_quat4_slerp(lx_quat a, lx_quat b, float t)
{

}

lx_quat lx_quat4_mul(lx_quat a, lx_quat b)
{

}

lx_quat lx_quat4_scale(lx_quat q, float scalar)
{

}

lx_vec3 lx_quat4_rotate_vec3(lx_quat q, lx_vec3 v)
{

}

int lx_quat4_equal(lx_quat a, lx_quat b, float epsilon)
{

}

lx_quat lx_quat4_look_rotation(lx_vec3 direction, lx_vec3 up)
{

}

