#include "lux/math.h"

lx_quat4f lx_quat4f_zero()
{

}

lx_quat4f lx_quat4f_identity()
{

}

lx_quat4f lx_quat4f_from_euler(float pitch, float yaw, float roll)
{

}

lx_quat4f lx_quat4f_from_axis(lx_vec3f axis, float angle)
{

}

lx_quat4f lx_quat4f_from_mat3f(lx_mat3f m)
{

}

lx_quat4f lx_quat4f_from_mat4f(lx_mat4f m)
{

}

lx_quat4f lx_quat4f_mul(lx_quat4f a, lx_quat4f b)
{

}

lx_quat4f lx_quat4f_scale_by_scalar(lx_quat4f q, float scale)
{

}

lx_quat4f lx_quat4f_normalize(lx_quat4f q)
{

}

lx_quat4f lx_quat4f_lerp(lx_quat4f a, lx_quat4f b, float t)
{

}

lx_quat4f lx_quat4f_slerp(lx_quat4f a, lx_quat4f b, float t)
{

}

lx_quat4f lx_quat4f_conjugate(lx_quat4f q)
{

}

lx_quat4f lx_quat4f_inverse(lx_quat4f q)
{

}

lx_quat4f lx_quat4f_look_rotation(lx_vec3f direction, lx_vec3f up)
{

}

float lx_quat4f_dot(lx_quat4f a, lx_quat4f b)
{

}

lx_vec3f lx_quat4f_rotate_vec3f(lx_quat4f q, lx_vec3f v)
{

}

lx_vec3f lx_quat4f_to_euler(lx_quat4f q)
{

}

int lx_quat4f_equal(lx_quat4f a, lx_quat4f b, float epsilon)
{

}
