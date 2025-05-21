/*
Utility functions for working with 3D vectors.
*/

#include "main.h"

// IN FILE:

t_vec3	vec3_new(double x, double y, double z);
t_vec3	vec3_norm(t_vec3 vec);
t_vec3	vec3_scale(t_vec3 v, double scalar);
double	vec3_length(t_vec3 v);

/**
Function to create a new 3D vector with specified x, y, and z components.
 @param x	The x-component of the vector.
 @param y	The y-component of the vector.
 @param z	The z-component of the vector.

 @return 	A new vector initialized with the given components.
*/
t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

/**
Function to normalize a 3D vector.
A vector is normalized when its length (or magnitude) is 1.0.
 @param v 	The vector to normalize.

 @return 	The normalized vector.

 @note
Due to floating-point precision limitations, comparing the vector's length
directly to zero can be unreliable. Instead, a small threshold (1e-6) is used.
This avoids dividing by extremely small values, which could lead to inaccuracies
or overflow errors. Values smaller than this threshold are considered too close
to zero for reliable normalization.
*/
t_vec3	vec3_norm(t_vec3 vec)
{
	double	length;
	double	inv_length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (length > 1e-6)
	{
		inv_length = 1.0 / length;
		vec.x *= inv_length;
		vec.y *= inv_length;
		vec.z *= inv_length;
	}
	return (vec);
}

/**
Function to scale a 3D vector by a scalar value.
 @param v 		The vector to scale.
 @param scalar 	The scalar value to multiply the vector by.

 @return 		The resulting scaled vector.
*/
t_vec3	vec3_scale(t_vec3 v, double scalar)
{
	t_vec3	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

/**
Function to calculate the length of a 3D vector (its magnitude).
 @param v 	The vector to calculate the length of.

 @return 	The length of the vector.
*/
double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
