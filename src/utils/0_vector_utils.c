/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_vector_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:35:34 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/04 09:18:14 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Utility functions for working with 3D vectors.
*/

#include "main.h"

// IN FILE:

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mult(t_vec3 v, double scalar);
double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_norm(t_vec3 v);

/**
Function to add two 3D vectors.

 @param v1 The first vector.
 @param v2 The second vector.

 @return   The resulting vector after addition.
*/
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return (result);
}

/**
Function to subtract two 3D vectors.
 @param v1 	The first vector.
 @param v2 	The second vector.

 @return 	The resulting vector after subtraction.
*/
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}


/**
Function to multiply a 3D vector by a scalar.

 @param v       The vector to be scaled.
 @param scalar  The scalar value to multiply the vector by.

 @return        The resulting vector after scaling.
*/
t_vec3	vec3_mult(t_vec3 v, double scalar)
{
	t_vec3	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

/**
Function to dot two vectors.
 @param v1 	The first vector.
 @param v2 	The second vector.

 @return 	The dot product of the two vectors.
*/
double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	double	result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (result);
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
t_vec3	vec3_norm(t_vec3 v)
{
	double	length;
	double	inv_length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length > 1e-6)
	{
		inv_length = 1.0 / length;
		v.x *= inv_length;
		v.y *= inv_length;
		v.z *= inv_length;
	}
	return (v);
}
