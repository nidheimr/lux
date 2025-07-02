#pragma once

#include "external.h"
LX_BEGIN_HEADER

//
//  types
//

typedef struct _lx_vec2f { float x, y; } lx_vec2f;
typedef struct _lx_vec3f { float x, y, z; } lx_vec3f;
typedef struct _lx_vec4f { float x, y, z, w; } lx_vec4f;
typedef struct _lx_mat2f { float m[2][2]; } lx_mat2f;
typedef struct _lx_mat3f { float m[3][3]; } lx_mat3f;
typedef struct _lx_mat4f { float m[4][4]; } lx_mat4f;
typedef struct _lx_quat4f { float x, y, z, w; } lx_quat4f;

//
//  utility
//

/**
 * @brief Clamps a float between two values.
 *
 * @param f The float.
 * @param min The minimum value.
 * @param max The maximum value.
 *
 * @return The clamped value.
 */
float lx_clampf(float f, float min, float max);

/**
 * @brief Linearly interpolates between two floats.
 *
 * @param a The source float.
 * @param b The destination float.
 * @param t The interpolation factor (between 0 and 1).
 *
 * @return The interpolated value.
 */
float lx_lerpf(float a, float b, float t);

/**
 * @brief Converts degrees to radians.
 *
 * @param degrees The degrees.
 *
 * @return The radian value.
 */
float lx_deg_to_rad(float degrees);

/**
 * @brief Converts radians to degrees.
 *
 * @param radians The radians.
 *
 * @return The degree value.
 */
float lx_rad_to_deg(float radians);

/**
 * @brief Checks if two floats are equal within an error margin.
 *
 * @param a The first float.
 * @param b The second float.
 * @param epsilon The allowed margin of error.
 *
 * @return 1 if the two floats are equal within the margin of error,
 * otherwise 0.
 */
int lx_float_equal(float a, float b, float epsilon);

//
//  vector 2f
//

lx_vec2f lx_vec2f_zero();
lx_vec2f lx_vec2f_from_vec3f(lx_vec3f v);
lx_vec2f lx_vec2f_from_vec4f(lx_vec4f v);

lx_vec2f lx_vec2f_add(lx_vec2f a, lx_vec2f b);
lx_vec2f lx_vec2f_sub(lx_vec2f a, lx_vec2f b);
lx_vec2f lx_vec2f_mul(lx_vec2f a, lx_vec2f b);
lx_vec2f lx_vec2f_scale_by_scalar(lx_vec2f v, float scale);
lx_vec2f lx_vec2f_normalize(lx_vec2f v);
lx_vec2f lx_vec2f_lerp(lx_vec2f a, lx_vec2f b, float t);
lx_vec2f lx_vec2f_clamp(lx_vec2f v, lx_vec2f min, lx_vec2f max);

float lx_vec2f_dot(lx_vec2f a, lx_vec2f b);
float lx_vec2f_length(lx_vec2f v);
float lx_vec2f_length_squared(lx_vec2f v);

int lx_vec2f_equal(lx_vec2f a, lx_vec2f b, float epsilon);

//
//  vector 3f
//

lx_vec3f lx_vec3f_zero();
lx_vec3f lx_vec3f_from_vec2f(lx_vec2f v);
lx_vec3f lx_vec3f_from_vec4f(lx_vec4f v);

lx_vec3f lx_vec3f_add(lx_vec3f a, lx_vec3f b);
lx_vec3f lx_vec3f_sub(lx_vec3f a, lx_vec3f b);
lx_vec3f lx_vec3f_mul(lx_vec3f a, lx_vec3f b);
lx_vec3f lx_vec3f_scale_by_scalar(lx_vec3f v, float scale);
lx_vec3f lx_vec3f_normalize(lx_vec3f v);
lx_vec3f lx_vec3f_lerp(lx_vec3f a, lx_vec3f b, float t);
lx_vec3f lx_vec3f_clamp(lx_vec3f v, lx_vec3f min, lx_vec3f max);
lx_vec3f lx_vec3f_reflect(lx_vec3f i, lx_vec3f n);

float lx_vec3f_dot(lx_vec3f a, lx_vec3f b);
float lx_vec3f_length(lx_vec3f v);
float lx_vec3f_length_squared(lx_vec3f v);
float lx_vec3f_distance(lx_vec3f a, lx_vec3f b);

int lx_vec3f_equal(lx_vec3f a, lx_vec3f b, float epsilon);

lx_vec3f lx_vec3f_cross(lx_vec3f a, lx_vec3f b);

//
//  vector 4f
//

lx_vec4f lx_vec4f_zero();
lx_vec4f lx_vec4f_from_vec2f(lx_vec2f v);
lx_vec4f lx_vec4f_from_vec3f(lx_vec3f v);

lx_vec4f lx_vec4f_add(lx_vec4f a, lx_vec4f b);
lx_vec4f lx_vec4f_sub(lx_vec4f a, lx_vec4f b);
lx_vec4f lx_vec4f_mul(lx_vec4f a, lx_vec4f b);
lx_vec4f lx_vec4f_scale_by_scalar(lx_vec4f v, float scale);
lx_vec4f lx_vec4f_normalize(lx_vec4f v);
lx_vec4f lx_vec4f_lerp(lx_vec4f a, lx_vec4f b, float t);
lx_vec4f lx_vec4f_clamp(lx_vec4f v, lx_vec4f min, lx_vec4f max);

float lx_vec4f_dot(lx_vec4f a, lx_vec4f b);
float lx_vec4f_length(lx_vec4f v);
float lx_vec4f_length_squared(lx_vec4f v);

int lx_vec4f_equal(lx_vec4f a, lx_vec4f b, float epsilon);

//
//  matrix 2f
//

lx_mat2f lx_mat2f_zero();
lx_mat2f lx_mat2f_identity();
lx_mat2f lx_mat2f_from_mat3f(lx_mat3f v);
lx_mat2f lx_mat2f_from_mat4f(lx_mat4f v);

lx_mat2f lx_mat2f_add(lx_mat2f a, lx_mat2f b);
lx_mat2f lx_mat2f_sub(lx_mat2f a, lx_mat2f b);
lx_mat2f lx_mat2f_mul(lx_mat2f a, lx_mat2f b);
lx_mat2f lx_mat2f_scale_by_scalar(lx_mat2f a, float scale);
lx_mat2f lx_mat2f_transpose(lx_mat2f m);
lx_mat2f lx_mat2f_inverse(lx_mat2f m);

lx_vec2f lx_mat2f_mul_vec2f(lx_mat2f m, lx_vec2f v);

int lx_mat2f_equal(lx_mat2f a, lx_mat2f b, float epsilon);

//
//  matrix 3f
//

lx_mat3f lx_mat3f_zero();
lx_mat3f lx_mat3f_identity();
lx_mat3f lx_mat3f_from_mat2f(lx_mat2f v);
lx_mat3f lx_mat3f_from_mat4f(lx_mat4f v);

lx_mat3f lx_mat3f_add(lx_mat3f a, lx_mat3f b);
lx_mat3f lx_mat3f_sub(lx_mat3f a, lx_mat3f b);
lx_mat3f lx_mat3f_mul(lx_mat3f a, lx_mat3f b);
lx_mat3f lx_mat3f_scale_by_scalar(lx_mat3f a, float scale);
lx_mat3f lx_mat3f_transpose(lx_mat3f m);
lx_mat3f lx_mat3f_inverse(lx_mat3f m);

lx_vec3f lx_mat3f_mul_vec3f(lx_mat3f m, lx_vec3f v);

int lx_mat3f_equal(lx_mat3f a, lx_mat3f b, float epsilon);

//
//  matrix 4f
//

lx_mat4f lx_mat4f_zero();
lx_mat4f lx_mat4f_identity();
lx_mat4f lx_mat4f_from_mat2f(lx_mat2f v);
lx_mat4f lx_mat4f_from_mat3f(lx_mat3f v);

lx_mat4f lx_mat4f_add(lx_mat4f a, lx_mat4f b);
lx_mat4f lx_mat4f_sub(lx_mat4f a, lx_mat4f b);
lx_mat4f lx_mat4f_mul(lx_mat4f a, lx_mat4f b);
lx_mat4f lx_mat4f_scale_by_scalar(lx_mat4f a, float scale);
lx_mat4f lx_mat4f_transpose(lx_mat4f m);
lx_mat4f lx_mat4f_inverse(lx_mat4f m);
lx_mat4f lx_mat4f_translate(lx_vec3f translation);
lx_mat4f lx_mat4f_scale(lx_vec3f scale);
lx_mat4f lx_mat4f_rotate(lx_vec3f axis, float degrees);
lx_mat4f lx_mat4f_look_at(lx_vec3f eye, lx_vec3f center, lx_vec3f up);
lx_mat4f lx_mat4f_perspective(float fov, float aspect, float near, float far);
lx_mat4f lx_mat4f_orthographic(float left, float right, float bottom, float top, float near, float far);

lx_vec4f lx_mat4f_mul_vec4f(lx_mat4f m, lx_vec4f v);

int lx_mat4f_equal(lx_mat4f a, lx_mat4f b, float epsilon);

//
//  quaternion 4f
//

lx_quat4f lx_quat4f_zero();
lx_quat4f lx_quat4f_identity();
lx_quat4f lx_quat4f_from_euler(float pitch, float yaw, float roll);
lx_quat4f lx_quat4f_from_axis(lx_vec3f axis, float angle);
lx_quat4f lx_quat4f_from_mat3f(lx_mat3f m);
lx_quat4f lx_quat4f_from_mat4f(lx_mat4f m);

lx_quat4f lx_quat4f_mul(lx_quat4f a, lx_quat4f b);
lx_quat4f lx_quat4f_scale_by_scalar(lx_quat4f q, float scale);
lx_quat4f lx_quat4f_normalize(lx_quat4f q);
lx_quat4f lx_quat4f_lerp(lx_quat4f a, lx_quat4f b, float t);
lx_quat4f lx_quat4f_slerp(lx_quat4f a, lx_quat4f b, float t);
lx_quat4f lx_quat4f_conjugate(lx_quat4f q);
lx_quat4f lx_quat4f_inverse(lx_quat4f q);
lx_quat4f lx_quat4f_look_rotation(lx_vec3f direction, lx_vec3f up);

float lx_quat4f_dot(lx_quat4f a, lx_quat4f b);

lx_vec3f lx_quat4f_rotate_vec3f(lx_quat4f q, lx_vec3f v);
lx_vec3f lx_quat4f_to_euler(lx_quat4f q);

int lx_quat4f_equal(lx_quat4f a, lx_quat4f b, float epsilon);

LX_END_HEADER
