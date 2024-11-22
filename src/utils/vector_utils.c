/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:35:34 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/22 18:34:03 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// IN FILE:

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_scale(t_vec3 v, double scalar);

/**
Function to subtract two vectors.
 @param v1 	The first vector.
 @param v2 	The second vector.

 @return 	The result of the subtraction of the two vectors (v1 - v2).
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
Function to multiply a vector by a scalar.
 @param v		The vector to scale.
 @param scalar 	The scalar value to multiply the vector by.

 @return 		The scaled vector.
*/
t_vec3	vec3_scale(t_vec3 v, double scalar)
{
	t_vec3	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}
