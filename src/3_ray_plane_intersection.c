/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ray_plane_intersection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/15 10:45:33 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains functions to calculate the intersection of a ray with a
plane object in 3D space.

See the README for more details on the mathematically derived ray-object
intersection algorithms used in the function below:
https://github.com/Busedame/miniRT/blob/main/README.md#ray-object-intersection
*/

#include "main.h"

// IN FILE:

int		ray_intersect_plane(t_vec3 ray_dir, t_obj *obj, double *t);

/**
Function to find the intersection of a ray with a plane.

 @param ray_origin 	The starting point of the ray (3D vector).
 @param ray_dir 	The normalized direction vector of the ray.
 @param plane 		Pointer to the plane structure.
 @param t 			A pointer to store the distance to the intersection point
 					(if found).

 @return 			`1` if an intersection is found in the FOV (and `t` is set
 					to the intersection distance);
					`0` if there is no intersection within the FOV (ray is
					parallel to the plane or intersection behind the camera).

 @note
Due to floating-point precision limitations, directly comparing a dot product
to zero can be unreliable. A small threshold (EPSILON -> 1e-6) is used to
determine if the ray is parallel to the plane. Values below this threshold are
considered too close to zero, indicating parallelism or preventing division by
very small numbers, which could lead to inaccuracies.
*/
int	ray_intersect_plane(t_vec3 ray_dir, t_obj *obj, double *t)
{
	double	denom;

	denom = vec3_dot(ray_dir, obj->x.pl.normal);
	if (fabs(denom) > EPSILON)
	{
		*t = obj->ixd.dot_diff_normal / denom;
		if (*t > 0.0)
			return (1);
	}
	return (0);
}
