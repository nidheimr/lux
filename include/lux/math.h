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

/**
 * @brief Creates a 2d vector with all zero values.
 *
 * @return The resulting vector.
 */
lx_vec2f lx_vec2f_zero();

/**
 * @brief Creates a 2d vector from a 3d vector, dropping the z value.
 *
 * @param v The 3d vector to convert.
 *
 * @return The resulting vector.
 */
lx_vec2f lx_vec2f_from_vec3f(lx_vec3f v);

/**
 * @brief Creates a 2d vector from a 4d vector, dropping the z, w values.
 *
 * @param v The 4d vector to convert.
 * 
 * @return The resulting vector.
 */
lx_vec2f lx_vec2f_from_vec4f(lx_vec4f v);

/**
 * @brief Adds the first vector and the second vector together.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The resulting vector.
 */
lx_vec2f lx_vec2f_add(lx_vec2f a, lx_vec2f b);

/**
 * @brief Subtracts the second vector from the first vector.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The resulting vector.
 */
lx_vec2f lx_vec2f_sub(lx_vec2f a, lx_vec2f b);

/**
 * @brief Multiplies the first vector and the second vector together.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The resulting vector.
 */
lx_vec2f lx_vec2f_mul(lx_vec2f a, lx_vec2f b);

/**
 * @brief Scales the vector by a scalar value.
 *
 * @param v The vector.
 * @param scale The scalar value.
 *
 * @return The resulting vector.
 */
lx_vec2f lx_vec2f_scale_by_scalar(lx_vec2f v, float scale);

/**
 * @brief Normilizes a vector.
 *
 * @param v The vector.
 *
 * @return The resulting vector.
 */
lx_vec2f lx_vec2f_normalize(lx_vec2f v);

/**
 * @brief Linearly interpolates between two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @param t The interpolation factor.
 *
 * @return The resulting vector.
 */
lx_vec2f lx_vec2f_lerp(lx_vec2f a, lx_vec2f b, float t);

/**
 * @brief Clamps a vector between two values.
 *
 * @param v The vector.
 * @param min The minimum vector.
 * @param max The maximum vector.
 */
lx_vec2f lx_vec2f_clamp(lx_vec2f v, lx_vec2f min, lx_vec2f max);

/**
 * @brief Calculates the dot product between two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The scalar dot product.
 */
float lx_vec2f_dot(lx_vec2f a, lx_vec2f b);

/**
 * @brief Calculates the magnitude/length of a vector.
 *
 * @param v The vector.
 *
 * @return The magnitude/length.
 */
float lx_vec2f_length(lx_vec2f v);

/**
 * @brief Calculates the square of the magnitude/length of a vector.
 *
 * @param v The vector.
 *
 * @return The squared magnitude/length.
 */
float lx_vec2f_length_squared(lx_vec2f v);

/**
 * @brief Checks if two vectors are equal within an error margin.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @param epsilon The allowed margin of error.
 *
 * @return 1 if the two vectors are equal within the margin of error,
 * otherwise 0.
 */
int lx_vec2f_equal(lx_vec2f a, lx_vec2f b, float epsilon);

//
//  vector 3f
//

/**
 * @brief Creates a 3d vector with all zero values.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_zero();

/**
 * @brief Creates a 3d vector from a 2d vector, adding a zero z value.
 *
 * @param v The 2d vector to convert.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_from_vec2f(lx_vec2f v);

/**
 * @brief Creates a 3d vector from a 4d vector, dropping the w value.
 *
 * @param v The 4d vector to convert.
 * 
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_from_vec4f(lx_vec4f v);

/**
 * @brief Adds the first vector and the second vector together.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_add(lx_vec3f a, lx_vec3f b);

/**
 * @brief Subtracts the second vector from the first vector.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_sub(lx_vec3f a, lx_vec3f b);

/**
 * @brief Multiplies the first vector and the second vector together.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_mul(lx_vec3f a, lx_vec3f b);

/**
 * @brief Scales the vector by a scalar value.
 *
 * @param v The vector.
 * @param scale The scalar value.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_scale_by_scalar(lx_vec3f v, float scale);

/**
 * @brief Normilizes a vector.
 *
 * @param v The vector.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_normalize(lx_vec3f v);

/**
 * @brief Linearly interpolates between two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @param t The interpolation factor.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_lerp(lx_vec3f a, lx_vec3f b, float t);

/**
 * @brief Clamps a vector between two values.
 *
 * @param v The vector.
 * @param min The minimum vector.
 * @param max The maximum vector.
 */
lx_vec3f lx_vec3f_clamp(lx_vec3f v, lx_vec3f min, lx_vec3f max);

/**
 * @brief Calculates the resulting reflection vector based on the incidence
 * and normal vectors.
 *
 * @param i The incident vector.
 * @param n The normal vector.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_vec3f_reflect(lx_vec3f i, lx_vec3f n);

/**
 * @brief Calculates the dot product between two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The scalar dot product.
 */
float lx_vec3f_dot(lx_vec3f a, lx_vec3f b);

/**
 * @brief Calculates the magnitude/length of a vector.
 *
 * @param v The vector.
 *
 * @return The magnitude/length.
 */
float lx_vec3f_length(lx_vec3f v);

/**
 * @brief Calculates the square of the magnitude/length of a vector.
 *
 * @param v The vector.
 *
 * @return The squared magnitude/length.
 */
float lx_vec3f_length_squared(lx_vec3f v);

/**
 * @brief Calculates the distance between two vectors in linear space.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The distance.
 */
float lx_vec3f_distance(lx_vec3f a, lx_vec3f b);

/**
 * @brief Checks if two vectors are equal within an error margin.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @param epsilon The allowed margin of error.
 *
 * @return 1 if the two vectors are equal within the margin of error,
 * otherwise 0.
 */
int lx_vec3f_equal(lx_vec3f a, lx_vec3f b, float epsilon);

/**
 * @brief Calculates a vector that is perpendicular to two other vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The cross product.
 */
lx_vec3f lx_vec3f_cross(lx_vec3f a, lx_vec3f b);

//
//  vector 4f
//

/**
 * @brief Creates a 4d vector with all zero values.
 *
 * @return The resulting vector.
 */
lx_vec4f lx_vec4f_zero();

/**
 * @brief Creates a 4d vector from a 2d vector, adding zero z, w values.
 *
 * @param v The 2d vector to convert.
 *
 * @return The resulting vector.
 */
lx_vec4f lx_vec4f_from_vec2f(lx_vec2f v);

/**
 * @brief Creates a 4d vector from a 3d vector, adding a zero w value.
 *
 * @param v The 4d vector to convert.
 * 
 * @return The resulting vector.
 */
lx_vec4f lx_vec4f_from_vec3f(lx_vec3f v);

/**
 * @brief Adds the first vector and the second vector together.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The resulting vector.
 */
lx_vec4f lx_vec4f_add(lx_vec4f a, lx_vec4f b);

/**
 * @brief Subtracts the second vector from the first vector.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The resulting vector.
 */
lx_vec4f lx_vec4f_sub(lx_vec4f a, lx_vec4f b);

/**
 * @brief Multiplies the first vector and the second vector together.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The resulting vector.
 */
lx_vec4f lx_vec4f_mul(lx_vec4f a, lx_vec4f b);

/**
 * @brief Scales the vector by a scalar value.
 *
 * @param v The vector.
 * @param scale The scalar value.
 *
 * @return The resulting vector.
 */
lx_vec4f lx_vec4f_scale_by_scalar(lx_vec4f v, float scale);

/**
 * @brief Normilizes a vector.
 *
 * @param v The vector.
 *
 * @return The resulting vector.
 */
lx_vec4f lx_vec4f_normalize(lx_vec4f v);

/**
 * @brief Linearly interpolates between two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @param t The interpolation factor.
 *
 * @return The resulting vector.
 */
lx_vec4f lx_vec4f_lerp(lx_vec4f a, lx_vec4f b, float t);

/**
 * @brief Clamps a vector between two values.
 *
 * @param v The vector.
 * @param min The minimum vector.
 * @param max The maximum vector.
 */
lx_vec4f lx_vec4f_clamp(lx_vec4f v, lx_vec4f min, lx_vec4f max);

/**
 * @brief Calculates the dot product between two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The scalar dot product.
 */
float lx_vec4f_dot(lx_vec4f a, lx_vec4f b);

/**
 * @brief Calculates the magnitude/length of a vector.
 *
 * @param v The vector.
 *
 * @return The magnitude/length.
 */
float lx_vec4f_length(lx_vec4f v);

/**
 * @brief Calculates the square of the magnitude/length of a vector.
 *
 * @param v The vector.
 *
 * @return The squared magnitude/length.
 */
float lx_vec4f_length_squared(lx_vec4f v);

/**
 * @brief Checks if two vectors are equal within an error margin.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @param epsilon The allowed margin of error.
 *
 * @return 1 if the two vectors are equal within the margin of error,
 * otherwise 0.
 */
int lx_vec4f_equal(lx_vec4f a, lx_vec4f b, float epsilon);

//
//  matrix 2f
//

/**
 * @brief Creates a 2d matrix with all zero values.
 *
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_zero();

/**
 * @brief Creates a 2d identity matrix.
 *
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_identity();

/**
 * @brief Creates a 2d matrix from a 3d matrix, dropping additional rows/columns.
 *
 * @param m The 3d matrix to convert.
 *
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_from_mat3f(lx_mat3f m);

/**
 * @brief Creates a 2d matrix from a 4d matrix, dropping additional rows/columns.
 *
 * @param m The 4d matrix to convert.
 * 
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_from_mat4f(lx_mat4f m);

/**
 * @brief Adds the first matrix and the second matrix together.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 *
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_add(lx_mat2f a, lx_mat2f b);

/**
 * @brief Subtracts the second matrix from the first matrix.
 *
 * @param a The first matrix. 
 * @param b The second matrix.
 *
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_sub(lx_mat2f a, lx_mat2f b);

/**
 * @brief Multiplies the first matrix and the second matrix together.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 *
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_mul(lx_mat2f a, lx_mat2f b);

/**
 * @brief Scales the matrix by a scalar value.
 *
 * @param v The matrix.
 * @param scale The scalar value.
 *
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_scale_by_scalar(lx_mat2f a, float scale);

/**
 * @brief Calculates the transpose of the matrix.
 *
 * @param m The matrix.
 *
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_transpose(lx_mat2f m);

/**
 * @brief Calculates the inverse of the matrix.
 *
 * @param m The matrix.
 *
 * @return The resulting matrix.
 */
lx_mat2f lx_mat2f_inverse(lx_mat2f m);

/**
 * @brief Multiplies the matrix and the vector together.
 *
 * @param m The matrix.
 * @param v The vector.
 *
 * @return The resulting vector.
 */
lx_vec2f lx_mat2f_mul_vec2f(lx_mat2f m, lx_vec2f v);

/**
 * @brief Checks if two matrices are equal within an error margin.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 * @param epsilon The allowed margin of error.
 *
 * @return 1 if the two matrices are equal within the margin of error,
 * otherwise 0.
 */
int lx_mat2f_equal(lx_mat2f a, lx_mat2f b, float epsilon);

//
//  matrix 3f
//

/**
 * @brief Creates a 3d matrix with all zero values.
 *
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_zero();

/**
 * @brief Creates a 3d identity matrix.
 *
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_identity();

/**
 * @brief Creates a 3d matrix from a 2d matrix, zeroing additional rows/columns.
 *
 * @param m The 2d matrix to convert.
 *
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_from_mat2f(lx_mat2f m);

/**
 * @brief Creates a 3d matrix from a 4d matrix, dropping additional rows/columns.
 *
 * @param m The 4d matrix to convert.
 * 
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_from_mat4f(lx_mat4f m);

/**
 * @brief Adds the first matrix and the second matrix together.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 *
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_add(lx_mat3f a, lx_mat3f b);

/**
 * @brief Subtracts the second matrix from the first matrix.
 *
 * @param a The first matrix. 
 * @param b The second matrix.
 *
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_sub(lx_mat3f a, lx_mat3f b);

/**
 * @brief Multiplies the first matrix and the second matrix together.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 *
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_mul(lx_mat3f a, lx_mat3f b);

/**
 * @brief Scales the matrix by a scalar value.
 *
 * @param v The matrix.
 * @param scale The scalar value.
 *
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_scale_by_scalar(lx_mat3f a, float scale);

/**
 * @brief Calculates the transpose of the matrix.
 *
 * @param m The matrix.
 *
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_transpose(lx_mat3f m);

/**
 * @brief Calculates the inverse of the matrix.
 *
 * @param m The matrix.
 *
 * @return The resulting matrix.
 */
lx_mat3f lx_mat3f_inverse(lx_mat3f m);

/**
 * @brief Multiplies the matrix and the vector together.
 *
 * @param m The matrix.
 * @param v The vector.
 *
 * @return The resulting vector.
 */
lx_vec3f lx_mat3f_mul_vec3f(lx_mat3f m, lx_vec3f v);

/**
 * @brief Checks if two matrices are equal within an error margin.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 * @param epsilon The allowed margin of error.
 *
 * @return 1 if the two matrices are equal within the margin of error,
 * otherwise 0.
 */
int lx_mat3f_equal(lx_mat3f a, lx_mat3f b, float epsilon);

//
//  matrix 4f
//

/**
 * @brief Creates a 4d matrix with all zero values.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_zero();

/**
 * @brief Creates a 4d identity matrix.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_identity();

/**
 * @brief Creates a 4d matrix from a 2d matrix, zeroing additional rows/columns.
 *
 * @param m The 2d matrix to convert.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_from_mat2f(lx_mat2f m);

/**
 * @brief Creates a 4d matrix from a 3d matrix, zeroing additional rows/columns.
 *
 * @param m The 3d matrix to convert.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_from_mat3f(lx_mat3f m);

/**
 * @brief Adds the first matrix and the second matrix together.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_add(lx_mat4f a, lx_mat4f b);

/**
 * @brief Subtracts the second matrix from the first matrix.
 *
 * @param a The first matrix. 
 * @param b The second matrix.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_sub(lx_mat4f a, lx_mat4f b);

/**
 * @brief Multiplies the first matrix and the second matrix together.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_mul(lx_mat4f a, lx_mat4f b);

/**
 * @brief Scales the matrix by a scalar value.
 *
 * @param v The matrix.
 * @param scale The scalar value.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_scale_by_scalar(lx_mat4f a, float scale);

/**
 * @brief Calculates the transpose of the matrix.
 *
 * @param m The matrix.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_transpose(lx_mat4f m);

/**
 * @brief Calculates the inverse of the matrix.
 *
 * @param m The matrix.
 *
 * @return The resulting matrix.
 */
lx_mat4f lx_mat4f_inverse(lx_mat4f m);

/**
 * @brief Multiplies the matrix and the vector together.
 *
 * @param m The matrix.
 * @param v The vector.
 *
 * @return The resulting vector.
 */
lx_vec4f lx_mat4f_mul_vec4f(lx_mat4f m, lx_vec4f v);

/**
 * @brief Checks if two matrices are equal within an error margin.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 * @param epsilon The allowed margin of error.
 *
 * @return 1 if the two matrices are equal within the margin of error,
 * otherwise 0.
 */
int lx_mat4f_equal(lx_mat4f a, lx_mat4f b, float epsilon);

LX_END_HEADER
