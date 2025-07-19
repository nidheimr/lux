#pragma once

#include "api.h"
LX_BEGIN_HEADER

// types
// ----------------------------------------------------------------

typedef struct _lx_vec2 { float x, y; } lx_vec2;
typedef struct _lx_vec3 { float x, y, z; } lx_vec3;
typedef struct _lx_vec4 { float x, y, z, w; } lx_vec4;
typedef struct _lx_mat2 { float m[4]; } lx_mat2;
typedef struct _lx_mat3 { float m[9]; } lx_mat3;
typedef struct _lx_mat4 { float m[16]; } lx_mat4;

// utility
// ----------------------------------------------------------------

/**
 * @brief Clamps a float between a minimum and maximum value.
 *
 * @param f The value to clamp.
 * @param min The minimum bound.
 * @param max The maximum bound.
 *
 * @return The clamped value.
 */
LX_API float lx_float_clamp(float f, float min, float max);

/**
 * @brief Linearly interpolates between two float values.
 *
 * @param a Start value.
 * @param b End value.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The interpolated float value.
 */
LX_API float lx_float_lerp(float a, float b, float t);

/**
 * @brief Checks if two floats are equal within a given epsilon.
 *
 * @param a First float.
 * @param b Second float.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
LX_API int lx_float_equal(float a, float b, float epsilon);

/**
 * @brief Converts degrees to radians.
 *
 * @param degrees Angle in degrees.
 *
 * @return Angle in radians.
 */
LX_API float lx_deg_to_rad(float degrees);

/**
 * @brief Converts radians to degrees.
 *
 * @param radians Angle in radians.
 *
 * @return Angle in degrees.
 */
LX_API float lx_rad_to_deg(float radians);

// vec2
// ----------------------------------------------------------------

/**
 * @brief Returns a zero-initialized 2D vector.
 *
 * @return A 2D vector with all components set to zero.
 */
LX_API lx_vec2 lx_vec2_zero();

/**
 * @brief Creates a 2D vector from a 3D vector by dropping the z component.
 *
 * @param v The 3D vector.
 *
 * @return A 2D vector.
 */
LX_API lx_vec2 lx_vec2_from_vec3(lx_vec3 v);

/**
 * @brief Creates a 2D vector from a 4D vector by dropping the z and w components.
 *
 * @param v The 4D vector.
 *
 * @return A 2D vector.
 */
LX_API lx_vec2 lx_vec2_from_vec4(lx_vec4 v);

/**
 * @brief Adds two 2D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The sum of the vectors.
 */
LX_API lx_vec2 lx_vec2_add(lx_vec2 a, lx_vec2 b);

/**
 * @brief Subtracts one 2D vector from another.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The result of a - b.
 */
LX_API lx_vec2 lx_vec2_sub(lx_vec2 a, lx_vec2 b);

/**
 * @brief Multiplies two 2D vectors component-wise.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The component-wise product.
 */
LX_API lx_vec2 lx_vec2_mul(lx_vec2 a, lx_vec2 b);

/**
 * @brief Scales a 2D vector by a scalar.
 *
 * @param v The vector.
 * @param scale The scalar value.
 *
 * @return The scaled vector.
 */
LX_API lx_vec2 lx_vec2_scale_by_scalar(lx_vec2 v, float scale);

/**
 * @brief Normalizes a 2D vector.
 *
 * @param v The vector to normalize.
 *
 * @return The normalized vector.
 */
LX_API lx_vec2 lx_vec2_normalize(lx_vec2 v);

/**
 * @brief Linearly interpolates between two 2D vectors.
 *
 * @param a Start vector.
 * @param b End vector.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The interpolated vector.
 */
LX_API lx_vec2 lx_vec2_lerp(lx_vec2 a, lx_vec2 b, float t);

/**
 * @brief Clamps each component of a 2D vector between the corresponding components of min and max.
 *
 * @param v The vector to clamp.
 * @param min Minimum vector.
 * @param max Maximum vector.
 *
 * @return The clamped vector.
 */
LX_API lx_vec2 lx_vec2_clamp(lx_vec2 v, lx_vec2 min, lx_vec2 max);

/**
 * @brief Computes the dot product of two 2D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The dot product.
 */
LX_API float lx_vec2_dot(lx_vec2 a, lx_vec2 b);

/**
 * @brief Computes the magnitude of a 2D vector.
 *
 * @param v The vector.
 *
 * @return The length of the vector.
 */
LX_API float lx_vec2_magnitude(lx_vec2 v);

/**
 * @brief Computes the squared magnitude of a 2D vector.
 *
 * @param v The vector.
 *
 * @return The squared length of the vector.
 */
LX_API float lx_vec2_magnitude_squared(lx_vec2 v);

/**
 * @brief Checks if two 2D vectors are equal within a given epsilon.
 *
 * @param a First vector.
 * @param b Second vector.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
LX_API int lx_vec2_equal(lx_vec2 a, lx_vec2 b, float epsilon);

// vec3
// ----------------------------------------------------------------

/**
 * @brief Returns a zero-initialized 3D vector.
 *
 * @return A 3D vector with all components set to zero.
 */
LX_API lx_vec3 lx_vec3_zero();

/**
 * @brief Creates a 3D vector from a 2D vector, setting z to 0.
 *
 * @param v The 2D vector.
 *
 * @return A 3D vector.
 */
LX_API lx_vec3 lx_vec3_from_vec2(lx_vec2 v);

/**
 * @brief Creates a 3D vector from a 4D vector by dropping the w component.
 *
 * @param v The 4D vector.
 *
 * @return A 3D vector.
 */
LX_API lx_vec3 lx_vec3_from_vec4(lx_vec4 v);

/**
 * @brief Adds two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The sum of the vectors.
 */
LX_API lx_vec3 lx_vec3_add(lx_vec3 a, lx_vec3 b);

/**
 * @brief Subtracts one 3D vector from another.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The result of a - b.
 */
LX_API lx_vec3 lx_vec3_sub(lx_vec3 a, lx_vec3 b);

/**
 * @brief Multiplies two 3D vectors component-wise.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The component-wise product.
 */
LX_API lx_vec3 lx_vec3_mul(lx_vec3 a, lx_vec3 b);

/**
 * @brief Scales a 3D vector by a scalar.
 *
 * @param v The vector.
 * @param scale The scalar value.
 *
 * @return The scaled vector.
 */
LX_API lx_vec3 lx_vec3_scale_by_scalar(lx_vec3 v, float scale);

/**
 * @brief Normalizes a 3D vector.
 *
 * @param v The vector to normalize.
 *
 * @return The normalized vector.
 */
LX_API lx_vec3 lx_vec3_normalize(lx_vec3 v);

/**
 * @brief Linearly interpolates between two 3D vectors.
 *
 * @param a Start vector.
 * @param b End vector.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The interpolated vector.
 */
LX_API lx_vec3 lx_vec3_lerp(lx_vec3 a, lx_vec3 b, float t);

/**
 * @brief Clamps each component of a 3D vector between the corresponding components of min and max.
 *
 * @param v The vector to clamp.
 * @param min Minimum vector.
 * @param max Maximum vector.
 *
 * @return The clamped vector.
 */
LX_API lx_vec3 lx_vec3_clamp(lx_vec3 v, lx_vec3 min, lx_vec3 max);

/**
 * @brief Reflects a vector around a normal.
 *
 * @param i The input vector.
 * @param n The normal vector (should be normalized).
 *
 * @return The reflected vector.
 */
LX_API lx_vec3 lx_vec3_reflect(lx_vec3 i, lx_vec3 n);

/**
 * @brief Computes the dot product of two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The dot product.
 */
LX_API float lx_vec3_dot(lx_vec3 a, lx_vec3 b);

/**
 * @brief Computes the magnitude of a 3D vector.
 *
 * @param v The vector.
 *
 * @return The length of the vector.
 */
LX_API float lx_vec3_magnitude(lx_vec3 v);

/**
 * @brief Computes the squared magnitude of a 3D vector.
 *
 * @param v The vector.
 *
 * @return The squared length of the vector.
 */
LX_API float lx_vec3_magnitude_squared(lx_vec3 v);

/**
 * @brief Computes the distance between two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The distance between the vectors.
 */
LX_API float lx_vec3_distance(lx_vec3 a, lx_vec3 b);

/**
 * @brief Checks if two 3D vectors are equal within a given epsilon.
 *
 * @param a First vector.
 * @param b Second vector.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
LX_API int lx_vec3_equal(lx_vec3 a, lx_vec3 b, float epsilon);

/**
 * @brief Computes the cross product of two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The cross product.
 */
LX_API lx_vec3 lx_vec3_cross(lx_vec3 a, lx_vec3 b);

// vec4
// ----------------------------------------------------------------

/**
 * @brief Returns a zero-initialized 4D vector.
 *
 * @return A 4D vector with all components set to zero.
 */
LX_API lx_vec4 lx_vec4_zero();

/**
 * @brief Creates a 4D vector from a 2D vector, setting z and w to 0.
 *
 * @param v The 2D vector.
 *
 * @return A 4D vector.
 */
LX_API lx_vec4 lx_vec4_from_vec2(lx_vec2 v);

/**
 * @brief Creates a 4D vector from a 3D vector, setting w to 0.
 *
 * @param v The 3D vector.
 *
 * @return A 4D vector.
 */
LX_API lx_vec4 lx_vec4_from_vec3(lx_vec3 v);

/**
 * @brief Adds two 4D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The sum of the vectors.
 */
LX_API lx_vec4 lx_vec4_add(lx_vec4 a, lx_vec4 b);

/**
 * @brief Subtracts one 4D vector from another.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The result of a - b.
 */
LX_API lx_vec4 lx_vec4_sub(lx_vec4 a, lx_vec4 b);

/**
 * @brief Multiplies two 4D vectors component-wise.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The component-wise product.
 */
LX_API lx_vec4 lx_vec4_mul(lx_vec4 a, lx_vec4 b);

/**
 * @brief Scales a 4D vector by a scalar.
 *
 * @param v The vector.
 * @param scale The scalar value.
 *
 * @return The scaled vector.
 */
LX_API lx_vec4 lx_vec4_scale_by_scalar(lx_vec4 v, float scale);

/**
 * @brief Normalizes a 4D vector.
 *
 * @param v The vector to normalize.
 *
 * @return The normalized vector.
 */
LX_API lx_vec4 lx_vec4_normalize(lx_vec4 v);

/**
 * @brief Linearly interpolates between two 4D vectors.
 *
 * @param a Start vector.
 * @param b End vector.
 * @param t Interpolation factor between 0 and 1.
 *
 * @return The interpolated vector.
 */
LX_API lx_vec4 lx_vec4_lerp(lx_vec4 a, lx_vec4 b, float t);

/**
 * @brief Clamps each component of a 4D vector between the corresponding components of min and max.
 *
 * @param v The vector to clamp.
 * @param min Minimum vector.
 * @param max Maximum vector.
 *
 * @return The clamped vector.
 */
LX_API lx_vec4 lx_vec4_clamp(lx_vec4 v, lx_vec4 min, lx_vec4 max);

/**
 * @brief Computes the dot product of two 4D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 *
 * @return The dot product.
 */
LX_API float lx_vec4_dot(lx_vec4 a, lx_vec4 b);

/**
 * @brief Computes the magnitude of a 4D vector.
 *
 * @param v The vector.
 *
 * @return The length of the vector.
 */
LX_API float lx_vec4_magnitude(lx_vec4 v);

/**
 * @brief Computes the squared magnitude of a 4D vector.
 *
 * @param v The vector.
 *
 * @return The squared length of the vector.
 */
LX_API float lx_vec4_magnitude_squared(lx_vec4 v);

/**
 * @brief Checks if two 4D vectors are equal within a given epsilon.
 *
 * @param a First vector.
 * @param b Second vector.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
LX_API int lx_vec4_equal(lx_vec4 a, lx_vec4 b, float epsilon);

// mat2
// ----------------------------------------------------------------

/**
 * @brief Returns a zero-initialized 2x2 matrix.
 *
 * @return A 2x2 matrix with all elements set to zero.
 */
LX_API lx_mat2 lx_mat2_zero();

/**
 * @brief Returns a 2x2 identity matrix.
 *
 * @return A 2x2 identity matrix.
 */
LX_API lx_mat2 lx_mat2_identity();

/**
 * @brief Creates a 2x2 matrix from the top-left of a 3x3 matrix.
 *
 * @param m The 3x3 matrix.
 *
 * @return A 2x2 matrix.
 */
LX_API lx_mat2 lx_mat2_from_mat3(lx_mat3 m);

/**
 * @brief Creates a 2x2 matrix from the top-left of a 4x4 matrix.
 *
 * @param m The 4x4 matrix.
 *
 * @return A 2x2 matrix.
 */
LX_API lx_mat2 lx_mat2_from_mat4(lx_mat4 m);

/**
 * @brief Adds two 2x2 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The sum of the matrices.
 */
LX_API lx_mat2 lx_mat2_add(lx_mat2 a, lx_mat2 b);

/**
 * @brief Subtracts one 2x2 matrix from another.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The result of a - b.
 */
LX_API lx_mat2 lx_mat2_sub(lx_mat2 a, lx_mat2 b);

/**
 * @brief Multiplies two 2x2 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The matrix product a * b.
 */
LX_API lx_mat2 lx_mat2_mul(lx_mat2 a, lx_mat2 b);

/**
 * @brief Scales a 2x2 matrix by a scalar.
 *
 * @param a The matrix.
 * @param scale The scalar value.
 *
 * @return The scaled matrix.
 */
LX_API lx_mat2 lx_mat2_scale_by_scalar(lx_mat2 a, float scale);

/**
 * @brief Returns the transpose of a 2x2 matrix.
 *
 * @param m The matrix to transpose.
 *
 * @return The transposed matrix.
 */
LX_API lx_mat2 lx_mat2_transpose(lx_mat2 m);

/**
 * @brief Returns the inverse of a 2x2 matrix.
 *
 * @param m The matrix to invert.
 *
 * @return The inverse matrix.
 */
LX_API lx_mat2 lx_mat2_inverse(lx_mat2 m);

/**
 * @brief Multiplies a 2x2 matrix by a 2D vector.
 *
 * @param m The matrix.
 * @param v The vector.
 *
 * @return The resulting vector.
 */
LX_API lx_vec2 lx_mat2_mul_vec2(lx_mat2 m, lx_vec2 v);

/**
 * @brief Checks if two 2x2 matrices are equal within a given epsilon.
 *
 * @param a First matrix.
 * @param b Second matrix.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
LX_API int lx_mat2_equal(lx_mat2 a, lx_mat2 b, float epsilon);

// mat3
// ----------------------------------------------------------------

/**
 * @brief Returns a zero-initialized 3x3 matrix.
 *
 * @return A 3x3 matrix with all elements set to zero.
 */
LX_API lx_mat3 lx_mat3_zero();

/**
 * @brief Returns a 3x3 identity matrix.
 *
 * @return A 3x3 identity matrix.
 */
LX_API lx_mat3 lx_mat3_identity();

/**
 * @brief Creates a 3x3 matrix from a 2x2 matrix (fills remaining values with
 * zero).
 *
 * @param m The 2x2 matrix.
 *
 * @return A 3x3 matrix.
 */
LX_API lx_mat3 lx_mat3_from_mat2(lx_mat2 m);

/**
 * @brief Creates a 3x3 matrix from the top-left of a 4x4 matrix.
 *
 * @param m The 4x4 matrix.
 *
 * @return A 3x3 matrix.
 */
LX_API lx_mat3 lx_mat3_from_mat4(lx_mat4 m);

/**
 * @brief Adds two 3x3 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The sum of the matrices.
 */
LX_API lx_mat3 lx_mat3_add(lx_mat3 a, lx_mat3 b);

/**
 * @brief Subtracts one 3x3 matrix from another.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The result of a - b.
 */
LX_API lx_mat3 lx_mat3_sub(lx_mat3 a, lx_mat3 b);

/**
 * @brief Multiplies two 3x3 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The matrix product a * b.
 */
LX_API lx_mat3 lx_mat3_mul(lx_mat3 a, lx_mat3 b);

/**
 * @brief Scales a 3x3 matrix by a scalar.
 *
 * @param a The matrix.
 * @param scale The scalar value.
 *
 * @return The scaled matrix.
 */
LX_API lx_mat3 lx_mat3_scale_by_scalar(lx_mat3 a, float scale);

/**
 * @brief Returns the transpose of a 3x3 matrix.
 *
 * @param m The matrix to transpose.
 *
 * @return The transposed matrix.
 */
LX_API lx_mat3 lx_mat3_transpose(lx_mat3 m);

/**
 * @brief Returns the inverse of a 3x3 matrix.
 *
 * @param m The matrix to invert.
 *
 * @return The inverse matrix.
 */
LX_API lx_mat3 lx_mat3_inverse(lx_mat3 m);

/**
 * @brief Multiplies a 3x3 matrix by a 3D vector.
 *
 * @param m The matrix.
 * @param v The vector.
 *
 * @return The resulting vector.
 */
LX_API lx_vec3 lx_mat3_mul_vec3(lx_mat3 m, lx_vec3 v);

/**
 * @brief Checks if two 3x3 matrices are equal within a given epsilon.
 *
 * @param a First matrix.
 * @param b Second matrix.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
LX_API int lx_mat3_equal(lx_mat3 a, lx_mat3 b, float epsilon);

// mat4
// ----------------------------------------------------------------

/**
 * @brief Returns a zero-initialized 4x4 matrix.
 *
 * @return A 4x4 matrix with all elements set to zero.
 */
LX_API lx_mat4 lx_mat4_zero();

/**
 * @brief Returns a 4x4 identity matrix.
 *
 * @return A 4x4 identity matrix.
 */
LX_API lx_mat4 lx_mat4_identity();

/**
 * @brief Creates a 4x4 matrix from a 2x2 matrix (fills remaining values with
 * zero).
 *
 * @param m The 2x2 matrix.
 *
 * @return A 4x4 matrix.
 */
LX_API lx_mat4 lx_mat4_from_mat2(lx_mat2 m);

/**
 * @brief Creates a 4x4 matrix from a 3x3 matrix (fills remaining values with
 * zero).
 *
 * @param m The 3x3 matrix.
 *
 * @return A 4x4 matrix.
 */
LX_API lx_mat4 lx_mat4_from_mat3(lx_mat3 m);

/**
 * @brief Adds two 4x4 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The sum of the matrices.
 */
LX_API lx_mat4 lx_mat4_add(lx_mat4 a, lx_mat4 b);

/**
 * @brief Subtracts one 4x4 matrix from another.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The result of a - b.
 */
LX_API lx_mat4 lx_mat4_sub(lx_mat4 a, lx_mat4 b);

/**
 * @brief Multiplies two 4x4 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 *
 * @return The matrix product a * b.
 */
LX_API lx_mat4 lx_mat4_mul(lx_mat4 a, lx_mat4 b);

/**
 * @brief Scales a 4x4 matrix by a scalar.
 *
 * @param a The matrix.
 * @param scale The scalar value.
 *
 * @return The scaled matrix.
 */
LX_API lx_mat4 lx_mat4_scale_by_scalar(lx_mat4 a, float scale);

/**
 * @brief Returns the transpose of a 4x4 matrix.
 *
 * @param m The matrix to transpose.
 *
 * @return The transposed matrix.
 */
LX_API lx_mat4 lx_mat4_transpose(lx_mat4 m);

/**
 * @brief Returns the inverse of a 4x4 matrix.
 *
 * @param m The matrix to invert.
 *
 * @return The inverse matrix.
 */
LX_API lx_mat4 lx_mat4_inverse(lx_mat4 m);

/**
 * @brief Applies a translation to the given 4x4 matrix.
 *
 * @param m The original matrix to translate.
 * @param translation The translation vector.
 *
 * @return The translated matrix.
 */
LX_API lx_mat4 lx_mat4_translate(lx_mat4 m, lx_vec3 translation);

/**
 * @brief Applies scaling to the given 4x4 matrix.
 *
 * @param m The original matrix to scale.
 * @param scale The scale factors for each axis.
 *
 * @return The scaled matrix.
 */
LX_API lx_mat4 lx_mat4_scale(lx_mat4 m, lx_vec3 scale);

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
LX_API lx_mat4 lx_mat4_rotate(lx_mat4 m, lx_vec3 axis, float degrees);

/**
 * @brief Creates a view matrix for a camera looking from eye towards center, with the specified up vector.
 *
 * @param eye The position of the camera.
 * @param center The target point the camera is looking at.
 * @param up The up direction vector for the camera.
 *
 * @return The resulting view matrix.
 */
LX_API lx_mat4 lx_mat4_look_at(lx_vec3 eye, lx_vec3 center, lx_vec3 up);


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
LX_API lx_mat4 lx_mat4_perspective(float fov, float aspect, float near, float far);

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
LX_API lx_mat4 lx_mat4_orthographic(float left, float right, float bottom, float top, float near, float far);

/**
 * @brief Multiplies a 4x4 matrix by a 4D vector.
 *
 * @param m The matrix.
 * @param v The vector.
 *
 * @return The resulting vector.
 */
LX_API lx_vec4 lx_mat4_mul_vec4(lx_mat4 m, lx_vec4 v);

/**
 * @brief Checks if two 4x4 matrices are equal within a given epsilon.
 *
 * @param a First matrix.
 * @param b Second matrix.
 * @param epsilon Tolerance for comparison.
 *
 * @return 1 if equal within epsilon, otherwise 0.
 */
LX_API int lx_mat4_equal(lx_mat4 a, lx_mat4 b, float epsilon);

LX_END_HEADER
