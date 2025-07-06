#pragma once

#include "external.h"
LX_BEGIN_HEADER

//
//  types
//

typedef struct _lx_vec2 { float x, y; } lx_vec2;
typedef struct _lx_vec3 { float x, y, z; } lx_vec3;
typedef struct _lx_vec4 { float x, y, z, w; } lx_vec4;
typedef struct _lx_mat2 { float m[2][2]; } lx_mat2;
typedef struct _lx_mat3 { float m[3][3]; } lx_mat3;
typedef struct _lx_mat4 { float m[4][4]; } lx_mat4;
typedef struct _lx_quat { float x, y, z, w; } lx_quat;

//
//  utility
//

/**
 * @brief Clamps a float between a minimum and maximum value.
 *
 * @param f The value to clamp.
 * @param min The minimum bound.
 * @param max The maximum bound.
 *
 * @return The clamped value.
 */
float lx_clampf(float f, float min, float max);

/**
 * @brief Linearly interpolates between two float values.
 *
 * @param a Start value.
 * @param b End value.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The interpolated float value.
 */
float lx_lerpf(float a, float b, float t);

/**
 * @brief Converts degrees to radians.
 *
 * @param degrees Angle in degrees.
 *
 * @return Angle in radians.
 */
float lx_deg_to_rad(float degrees);

/**
 * @brief Converts radians to degrees.
 *
 * @param radians Angle in radians.
 *
 * @return Angle in degrees.
 */
float lx_rad_to_deg(float radians);

/**
 * @brief Checks if two floats are equal within a given epsilon.
 *
 * @param a First float.
 * @param b Second float.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
int lx_float_equal(float a, float b, float epsilon);

//
//  vec2
//

/**
 * @brief Returns a zero-initialized 2D vector.
 *
 * @return A 2D vector with all components set to zero.
 */
lx_vec2 lx_vec2_zero();

/**
 * @brief Creates a 2D vector from a 3D vector by dropping the z component.
 *
 * @param v The 3D vector.
 *
 * @return A 2D vector.
 */
lx_vec2 lx_vec2_from_vec3(lx_vec3 v);

/**
 * @brief Creates a 2D vector from a 4D vector by dropping the z and w components.
 *
 * @param v The 4D vector.
 *
 * @return A 2D vector.
 */
lx_vec2 lx_vec2_from_vec4(lx_vec4 v);

/**
 * @brief Adds two 2D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The sum of the vectors.
 */
lx_vec2 lx_vec2_add(lx_vec2 a, lx_vec2 b);

/**
 * @brief Subtracts one 2D vector from another.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The result of a - b.
 */
lx_vec2 lx_vec2_sub(lx_vec2 a, lx_vec2 b);

/**
 * @brief Multiplies two 2D vectors component-wise.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The component-wise product.
 */
lx_vec2 lx_vec2_mul(lx_vec2 a, lx_vec2 b);

/**
 * @brief Scales a 2D vector by a scalar.
 *
 * @param v The vector.
 * @param scale The scalar value.
 *
 * @return The scaled vector.
 */
lx_vec2 lx_vec2_scale_by_scalar(lx_vec2 v, float scale);

/**
 * @brief Normalizes a 2D vector.
 *
 * @param v The vector to normalize.
 *
 * @return The normalized vector.
 */
lx_vec2 lx_vec2_normalize(lx_vec2 v);

/**
 * @brief Linearly interpolates between two 2D vectors.
 *
 * @param a Start vector.
 * @param b End vector.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The interpolated vector.
 */
lx_vec2 lx_vec2_lerp(lx_vec2 a, lx_vec2 b, float t);

/**
 * @brief Clamps each component of a 2D vector between the corresponding components of min and max.
 *
 * @param v The vector to clamp.
 * @param min Minimum vector.
 * @param max Maximum vector.
 *
 * @return The clamped vector.
 */
lx_vec2 lx_vec2_clamp(lx_vec2 v, lx_vec2 min, lx_vec2 max);

/**
 * @brief Computes the dot product of two 2D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The dot product.
 */
float lx_vec2_dot(lx_vec2 a, lx_vec2 b);


/**
 * @brief Computes the magnitude of a 2D vector.
 *
 * @param v The vector.
 *
 * @return The length of the vector.
 */
float lx_vec2_magnitude(lx_vec2 v);

/**
 * @brief Computes the squared magnitude of a 2D vector.
 *
 * @param v The vector.
 *
 * @return The squared length of the vector.
 */
float lx_vec2_magnitude_squared(lx_vec2 v);

/**
 * @brief Checks if two 2D vectors are equal within a given epsilon.
 *
 * @param a First vector.
 * @param b Second vector.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
int lx_vec2_equal(lx_vec2 a, lx_vec2 b, float epsilon);

//
//  vec3
//

/**
 * @brief Returns a zero-initialized 3D vector.
 *
 * @return A 3D vector with all components set to zero.
 */
lx_vec3 lx_vec3_zero();

/**
 * @brief Creates a 3D vector from a 2D vector, setting z to 0.
 *
 * @param v The 2D vector.
 *
 * @return A 3D vector.
 */
lx_vec3 lx_vec3_from_vec2(lx_vec2 v);

/**
 * @brief Creates a 3D vector from a 4D vector by dropping the w component.
 *
 * @param v The 4D vector.
 *
 * @return A 3D vector.
 */
lx_vec3 lx_vec3_from_vec4(lx_vec4 v);

/**
 * @brief Adds two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The sum of the vectors.
 */
lx_vec3 lx_vec3_add(lx_vec3 a, lx_vec3 b);

/**
 * @brief Subtracts one 3D vector from another.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The result of a - b.
 */
lx_vec3 lx_vec3_sub(lx_vec3 a, lx_vec3 b);

/**
 * @brief Multiplies two 3D vectors component-wise.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The component-wise product.
 */
lx_vec3 lx_vec3_mul(lx_vec3 a, lx_vec3 b);

/**
 * @brief Scales a 3D vector by a scalar.
 *
 * @param v The vector.
 * @param scale The scalar value.
 *
 * @return The scaled vector.
 */
lx_vec3 lx_vec3_scale_by_scalar(lx_vec3 v, float scale);

/**
 * @brief Normalizes a 3D vector.
 *
 * @param v The vector to normalize.
 *
 * @return The normalized vector.
 */
lx_vec3 lx_vec3_normalize(lx_vec3 v);

/**
 * @brief Linearly interpolates between two 3D vectors.
 *
 * @param a Start vector.
 * @param b End vector.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The interpolated vector.
 */
lx_vec3 lx_vec3_lerp(lx_vec3 a, lx_vec3 b, float t);

/**
 * @brief Clamps each component of a 3D vector between the corresponding components of min and max.
 *
 * @param v The vector to clamp.
 * @param min Minimum vector.
 * @param max Maximum vector.
 *
 * @return The clamped vector.
 */
lx_vec3 lx_vec3_clamp(lx_vec3 v, lx_vec3 min, lx_vec3 max);

/**
 * @brief Reflects a vector around a normal.
 *
 * @param i The input vector.
 * @param n The normal vector (should be normalized).
 *
 * @return The reflected vector.
 */
lx_vec3 lx_vec3_reflect(lx_vec3 i, lx_vec3 n);

/**
 * @brief Computes the dot product of two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The dot product.
 */
float lx_vec3_dot(lx_vec3 a, lx_vec3 b);

/**
 * @brief Computes the magnitude of a 3D vector.
 *
 * @param v The vector.
 *
 * @return The length of the vector.
 */
float lx_vec3_magnitude(lx_vec3 v);

/**
 * @brief Computes the squared magnitude of a 3D vector.
 *
 * @param v The vector.
 *
 * @return The squared length of the vector.
 */
float lx_vec3_magnitude_squared(lx_vec3 v);

/**
 * @brief Computes the distance between two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The distance between the vectors.
 */
float lx_vec3_distance(lx_vec3 a, lx_vec3 b);

/**
 * @brief Checks if two 3D vectors are equal within a given epsilon.
 *
 * @param a First vector.
 * @param b Second vector.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
int lx_vec3_equal(lx_vec3 a, lx_vec3 b, float epsilon);

/**
 * @brief Computes the cross product of two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The cross product.
 */
lx_vec3 lx_vec3_cross(lx_vec3 a, lx_vec3 b);

//
//  vec4
//

/**
 * @brief Returns a zero-initialized 4D vector.
 *
 * @return A 4D vector with all components set to zero.
 */
lx_vec4 lx_vec4_zero();

/**
 * @brief Creates a 4D vector from a 2D vector, setting z and w to 0.
 *
 * @param v The 2D vector.
 *
 * @return A 4D vector.
 */
lx_vec4 lx_vec4_from_vec2(lx_vec2 v);

/**
 * @brief Creates a 4D vector from a 3D vector, setting w to 0.
 *
 * @param v The 3D vector.
 *
 * @return A 4D vector.
 */
lx_vec4 lx_vec4_from_vec3(lx_vec3 v);

/**
 * @brief Adds two 4D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The sum of the vectors.
 */
lx_vec4 lx_vec4_add(lx_vec4 a, lx_vec4 b);

/**
 * @brief Subtracts one 4D vector from another.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The result of a - b.
 */
lx_vec4 lx_vec4_sub(lx_vec4 a, lx_vec4 b);

/**
 * @brief Multiplies two 4D vectors component-wise.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The component-wise product.
 */
lx_vec4 lx_vec4_mul(lx_vec4 a, lx_vec4 b);

/**
 * @brief Scales a 4D vector by a scalar.
 *
 * @param v The vector.
 * @param scale The scalar value.
 *
 * @return The scaled vector.
 */
lx_vec4 lx_vec4_scale_by_scalar(lx_vec4 v, float scale);

/**
 * @brief Normalizes a 4D vector.
 *
 * @param v The vector to normalize.
 *
 * @return The normalized vector.
 */
lx_vec4 lx_vec4_normalize(lx_vec4 v);

/**
 * @brief Linearly interpolates between two 4D vectors.
 *
 * @param a Start vector.
 * @param b End vector.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The interpolated vector.
 */
lx_vec4 lx_vec4_lerp(lx_vec4 a, lx_vec4 b, float t);

/**
 * @brief Clamps each component of a 4D vector between the corresponding components of min and max.
 *
 * @param v The vector to clamp.
 * @param min Minimum vector.
 * @param max Maximum vector.
 *
 * @return The clamped vector.
 */
lx_vec4 lx_vec4_clamp(lx_vec4 v, lx_vec4 min, lx_vec4 max);

/**
 * @brief Computes the dot product of two 4D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The dot product.
 */
float lx_vec4_dot(lx_vec4 a, lx_vec4 b);

/**
 * @brief Computes the magnitude of a 4D vector.
 *
 * @param v The vector.
 *
 * @return The length of the vector.
 */
float lx_vec4_magnitude(lx_vec4 v);

/**
 * @brief Computes the squared magnitude of a 4D vector.
 *
 * @param v The vector.
 *
 * @return The squared length of the vector.
 */
float lx_vec4_magnitude_squared(lx_vec4 v);

/**
 * @brief Checks if two 4D vectors are equal within a given epsilon.
 *
 * @param a First vector.
 * @param b Second vector.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
int lx_vec4_equal(lx_vec4 a, lx_vec4 b, float epsilon);

//
//  mat2
//

/**
 * @brief Returns a zero-initialized 2x2 matrix.
 *
 * @return A 2x2 matrix with all elements set to zero.
 */
lx_mat2 lx_mat2_zero();

/**
 * @brief Returns a 2x2 identity matrix.
 *
 * @return A 2x2 identity matrix.
 */
lx_mat2 lx_mat2_identity();

/**
 * @brief Creates a 2x2 matrix from the top-left of a 3x3 matrix.
 *
 * @param m The 3x3 matrix.
 *
 * @return A 2x2 matrix.
 */
lx_mat2 lx_mat2_from_mat3(lx_mat3 m);

/**
 * @brief Creates a 2x2 matrix from the top-left of a 4x4 matrix.
 *
 * @param m The 4x4 matrix.
 *
 * @return A 2x2 matrix.
 */
lx_mat2 lx_mat2_from_mat4(lx_mat4 m);

/**
 * @brief Adds two 2x2 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The sum of the matrices.
 */
lx_mat2 lx_mat2_add(lx_mat2 a, lx_mat2 b);

/**
 * @brief Subtracts one 2x2 matrix from another.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The result of a - b.
 */
lx_mat2 lx_mat2_sub(lx_mat2 a, lx_mat2 b);

/**
 * @brief Multiplies two 2x2 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The matrix product a * b.
 */
lx_mat2 lx_mat2_mul(lx_mat2 a, lx_mat2 b);

/**
 * @brief Scales a 2x2 matrix by a scalar.
 *
 * @param a The matrix.
 * @param scale The scalar value.
 *
 * @return The scaled matrix.
 */
lx_mat2 lx_mat2_scale_by_scalar(lx_mat2 a, float scale);

/**
 * @brief Returns the transpose of a 2x2 matrix.
 *
 * @param m The matrix to transpose.
 *
 * @return The transposed matrix.
 */
lx_mat2 lx_mat2_transpose(lx_mat2 m);

/**
 * @brief Returns the inverse of a 2x2 matrix.
 *
 * @param m The matrix to invert.
 *
 * @return The inverse matrix.
 */
lx_mat2 lx_mat2_inverse(lx_mat2 m);

/**
 * @brief Multiplies a 2x2 matrix by a 2D vector.
 *
 * @param m The matrix.
 * @param v The vector.
 *
 * @return The resulting vector.
 */
lx_vec2 lx_mat2_mul_vec2(lx_mat2 m, lx_vec2 v);

/**
 * @brief Checks if two 2x2 matrices are equal within a given epsilon.
 *
 * @param a First matrix.
 * @param b Second matrix.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
int lx_mat2_equal(lx_mat2 a, lx_mat2 b, float epsilon);

//
//  mat3
//

/**
 * @brief Returns a zero-initialized 3x3 matrix.
 *
 * @return A 3x3 matrix with all elements set to zero.
 */
lx_mat3 lx_mat3_zero();

/**
 * @brief Returns a 3x3 identity matrix.
 *
 * @return A 3x3 identity matrix.
 */
lx_mat3 lx_mat3_identity();

/**
 * @brief Creates a 3x3 matrix from a 2x2 matrix (fills remaining values with identity components).
 *
 * @param m The 2x2 matrix.
 *
 * @return A 3x3 matrix.
 */
lx_mat3 lx_mat3_from_mat2(lx_mat2 m);

/**
 * @brief Creates a 3x3 matrix from the top-left of a 4x4 matrix.
 *
 * @param m The 4x4 matrix.
 *
 * @return A 3x3 matrix.
 */
lx_mat3 lx_mat3_from_mat4(lx_mat4 m);

/**
 * @brief Adds two 3x3 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The sum of the matrices.
 */
lx_mat3 lx_mat3_add(lx_mat3 a, lx_mat3 b);

/**
 * @brief Subtracts one 3x3 matrix from another.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The result of a - b.
 */
lx_mat3 lx_mat3_sub(lx_mat3 a, lx_mat3 b);

/**
 * @brief Multiplies two 3x3 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The matrix product a * b.
 */
lx_mat3 lx_mat3_mul(lx_mat3 a, lx_mat3 b);

/**
 * @brief Scales a 3x3 matrix by a scalar.
 *
 * @param a The matrix.
 * @param scale The scalar value.
 *
 * @return The scaled matrix.
 */
lx_mat3 lx_mat3_scale_by_scalar(lx_mat3 a, float scale);

/**
 * @brief Returns the transpose of a 3x3 matrix.
 *
 * @param m The matrix to transpose.
 *
 * @return The transposed matrix.
 */
lx_mat3 lx_mat3_transpose(lx_mat3 m);

/**
 * @brief Returns the inverse of a 3x3 matrix.
 *
 * @param m The matrix to invert.
 *
 * @return The inverse matrix.
 */
lx_mat3 lx_mat3_inverse(lx_mat3 m);

/**
 * @brief Multiplies a 3x3 matrix by a 3D vector.
 *
 * @param m The matrix.
 * @param v The vector.
 *
 * @return The resulting vector.
 */
lx_vec3 lx_mat3_mul_vec3(lx_mat3 m, lx_vec3 v);

/**
 * @brief Checks if two 3x3 matrices are equal within a given epsilon.
 *
 * @param a First matrix.
 * @param b Second matrix.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
int lx_mat3_equal(lx_mat3 a, lx_mat3 b, float epsilon);

//
//  mat4
//

/**
 * @brief Returns a zero-initialized 4x4 matrix.
 *
 * @return A 4x4 matrix with all elements set to zero.
 */
lx_mat4 lx_mat4_zero();

/**
 * @brief Returns a 4x4 identity matrix.
 *
 * @return A 4x4 identity matrix.
 */
lx_mat4 lx_mat4_identity();

/**
 * @brief Creates a 4x4 matrix from a 2x2 matrix (fills remaining values with identity components).
 *
 * @param m The 2x2 matrix.
 *
 * @return A 4x4 matrix.
 */
lx_mat4 lx_mat4_from_mat2(lx_mat2 m);

/**
 * @brief Creates a 4x4 matrix from a 3x3 matrix (fills remaining values with identity components).
 *
 * @param m The 3x3 matrix.
 *
 * @return A 4x4 matrix.
 */
lx_mat4 lx_mat4_from_mat3(lx_mat3 m);

/**
 * @brief Adds two 4x4 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The sum of the matrices.
 */
lx_mat4 lx_mat4_add(lx_mat4 a, lx_mat4 b);

/**
 * @brief Subtracts one 4x4 matrix from another.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The result of a - b.
 */
lx_mat4 lx_mat4_sub(lx_mat4 a, lx_mat4 b);

/**
 * @brief Multiplies two 4x4 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The matrix product a * b.
 */
lx_mat4 lx_mat4_mul(lx_mat4 a, lx_mat4 b);

/**
 * @brief Scales a 4x4 matrix by a scalar.
 *
 * @param a The matrix.
 * @param scale The scalar value.
 *
 * @return The scaled matrix.
 */
lx_mat4 lx_mat4_scale_by_scalar(lx_mat4 a, float scale);

/**
 * @brief Returns the transpose of a 4x4 matrix.
 *
 * @param m The matrix to transpose.
 *
 * @return The transposed matrix.
 */
lx_mat4 lx_mat4_transpose(lx_mat4 m);

/**
 * @brief Returns the inverse of a 4x4 matrix.
 *
 * @param m The matrix to invert.
 *
 * @return The inverse matrix.
 */
lx_mat4 lx_mat4_inverse(lx_mat4 m);

/**
 * @brief Applies a translation to the given 4x4 matrix.
 *
 * @param m The original matrix to translate.
 * @param translation The translation vector.
 *
 * @return The translated matrix.
 */
lx_mat4 lx_mat4_translate(lx_mat4 m, lx_vec3 translation);

/**
 * @brief Applies scaling to the given 4x4 matrix.
 *
 * @param m The original matrix to scale.
 * @param scale The scale factors for each axis.
 *
 * @return The scaled matrix.
 */
lx_mat4 lx_mat4_scale(lx_mat4 m, lx_vec3 scale);

/**
 * @brief Rotates a 4x4 matrix around an arbitrary axis by a specified angle.
 *
 * Only one axis should be used at a time; combining multiple axes in the
 * axis vector may cause incorrect rotation or artifacts.
 *
 * @param m The original matrix to rotate.
 * @param axis The axis vector around which to rotate.
 * @param degrees The rotation angle in degrees.
 *
 * @return The rotated matrix.
 */
lx_mat4 lx_mat4_rotate_axis_angle(lx_mat4 m, lx_vec3 axis, float degrees);

/**
 * @brief Rotates a 4x4 matrix by Euler angles (pitch, yaw, roll).
 *
 * @param m The original matrix to rotate.
 * @param pitch Rotation around the X-axis in degrees.
 * @param yaw Rotation around the Y-axis in degrees.
 * @param roll Rotation around the Z-axis in degrees.
 *
 * @return The rotated matrix.
 */
lx_mat4 lx_mat4_rotate_euler(lx_mat4 m, float pitch, float yaw, float roll);

/**
 * @brief Creates a view matrix for a camera looking from eye towards center, with the specified up vector.
 *
 * @param eye The position of the camera.
 * @param center The target point the camera is looking at.
 * @param up The up direction vector for the camera.
 *
 * @return The resulting view matrix.
 */
lx_mat4 lx_mat4_look_at(lx_vec3 eye, lx_vec3 center, lx_vec3 up);


/**
 * @brief Creates a perspective projection matrix.
 *
 * @param fov The vertical field of view in degrees.
 * @param aspect The aspect ratio (width divided by height).
 * @param near The near clipping plane distance.
 * @param far The far clipping plane distance.
 *
 * @return The perspective projection matrix.
 */
lx_mat4 lx_mat4_perspective(float fov, float aspect, float near, float far);

/**
 * @brief Creates an orthographic projection matrix.
 *
 * @param left The left clipping plane.
 * @param right The right clipping plane.
 * @param bottom The bottom clipping plane.
 * @param top The top clipping plane.
 * @param near The near clipping plane.
 * @param far The far clipping plane.
 *
 * @return The orthographic projection matrix.
 */
lx_mat4 lx_mat4_orthographic(float left, float right, float bottom, float top, float near, float far);

/**
 * @brief Multiplies a 4x4 matrix by a 4D vector.
 *
 * @param m The matrix.
 * @param v The vector.
 *
 * @return The resulting vector.
 */
lx_vec4 lx_mat4_mul_vec4(lx_mat4 m, lx_vec4 v);

/**
 * @brief Checks if two 4x4 matrices are equal within a given epsilon.
 *
 * @param a First matrix.
 * @param b Second matrix.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
int lx_mat4_equal(lx_mat4 a, lx_mat4 b, float epsilon);

//
//  quat
//

/**
 * @brief Returns a quaternion with all components set to zero.
 *
 * @return A zero-initialized quaternion.
 */
lx_quat lx_quat_zero();

/**
 * @brief Returns the identity quaternion (no rotation).
 *
 * @return The identity quaternion.
 */
lx_quat lx_quat_identity();

/**
 * @brief Creates a quaternion from an axis and angle (in degrees).
 *
 * @param axis The axis to rotate around.
 * @param angle The angle of rotation in degrees.
 *
 * @return The resulting quaternion.
 */
lx_quat lx_quat_from_axis_angle(lx_vec3 axis, float angle);

/**
 * @brief Creates a quaternion from Euler angles (in degrees).
 *
 * @param pitch Rotation around the X-axis.
 * @param yaw Rotation around the Y-axis.
 * @param roll Rotation around the Z-axis.
 *
 * @return The resulting quaternion.
 */
lx_quat lx_quat_from_euler(float pitch, float yaw, float roll);

/**
 * @brief Converts a 3x3 rotation matrix to a quaternion.
 *
 * @param m The 3x3 matrix to convert.
 *
 * @return The resulting quaternion.
 */
lx_quat lx_quat_from_mat3(lx_mat3 m);

/**
 * @brief Converts a 4x4 matrix to a quaternion.
 *
 * @param m The 4x4 matrix to convert.
 *
 * @return The resulting quaternion.
 */
lx_quat lx_quat_from_mat4(lx_mat4 m);

/**
 * @brief Converts a quaternion to a 3x3 rotation matrix.
 *
 * @param q The quaternion to convert.
 *
 * @return The resulting 3x3 matrix.
 */
lx_mat3 lx_quat_to_mat3(lx_quat q);

/**
 * @brief Converts a quaternion to a 4x4 rotation matrix.
 *
 * @param q The quaternion to convert.
 *
 * @return The resulting 4x4 matrix.
 */
lx_mat4 lx_quat_to_mat4(lx_quat q);

/**
 * @brief Converts a quaternion to Euler angles (in degrees).
 *
 * @param q The quaternion to convert.
 *
 * @return A vector containing pitch (x), yaw (y), and roll (z) in degrees.
 */
lx_vec3 lx_quat_to_euler(lx_quat q);

/**
 * @brief Returns the conjugate of a quaternion.
 *
 * @param q The input quaternion.
 *
 * @return The conjugated quaternion.
 */
lx_quat lx_quat4_conjugate(lx_quat q);

/**
 * @brief Returns the inverse of a quaternion.
 *
 * @param q The input quaternion.
 *
 * @return The inverse quaternion.
 */
lx_quat lx_quat4_inverse(lx_quat q);

/**
 * @brief Normalizes the quaternion to unit length.
 *
 * @param q The input quaternion.
 *
 * @return The normalized quaternion.
 */
lx_quat lx_quat4_normalize(lx_quat q);

/**
 * @brief Returns the magnitude of a quaternion.
 *
 * @param q The input quaternion.
 *
 * @return The length of the quaternion.
 */
float lx_quat4_magnitude(lx_quat q);

/**
 * @brief Computes the dot product between two quaternions.
 *
 * @param a The first quaternion.
 * @param b The second quaternion.
 *
 * @return The dot product.
 */
float lx_quat4_dot(lx_quat a, lx_quat b);

/**
 * @brief Linearly interpolates between two quaternions.
 *
 * @param a The start quaternion.
 * @param b The end quaternion.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The interpolated quaternion.
 */
lx_quat lx_quat4_lerp(lx_quat a, lx_quat b, float t);

/**
 * @brief Spherically interpolates between two quaternions.
 *
 * @param a The start quaternion.
 * @param b The end quaternion.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The spherically interpolated quaternion.
 */
lx_quat lx_quat4_slerp(lx_quat a, lx_quat b, float t);

/**
 * @brief Multiplies two quaternions (combines rotations).
 *
 * @param a The first quaternion.
 * @param b The second quaternion.
 *
 * @return The result of the multiplication.
 */
lx_quat lx_quat4_mul(lx_quat a, lx_quat b);

/**
 * @brief Scales each component of the quaternion by a scalar.
 *
 * @param q The quaternion to scale.
 * @param scalar The scalar value.
 *
 * @return The scaled quaternion.
 */
lx_quat lx_quat4_scale(lx_quat q, float scalar);

/**
 * @brief Rotates a vector by a quaternion.
 *
 * @param q The quaternion to rotate with.
 * @param v The vector to rotate.
 *
 * @return The rotated vector.
 */
lx_vec3 lx_quat4_rotate_vec3(lx_quat q, lx_vec3 v);

/**
 * @brief Checks if two quaternions are equal within a given epsilon.
 *
 * @param a The first quaternion.
 * @param b The second quaternion.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, 0 otherwise.
 */
int lx_quat4_equal(lx_quat a, lx_quat b, float epsilon);

/**
 * @brief Constructs a quaternion that looks in a given direction.
 *
 * @param direction The target direction to look toward.
 * @param up The up direction to align with.
 *
 * @return The resulting quaternion.
 */
lx_quat lx_quat4_look_rotation(lx_vec3 direction, lx_vec3 up);

LX_END_HEADER
