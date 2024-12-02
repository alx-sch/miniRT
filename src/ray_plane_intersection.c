/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/02 20:01:49 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "main.h"

// IN FILE:

int		ray_intersect_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane *plane,
			double *t);

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
					parallel to the plane or intersection is behind the camera).

 @details
See details of the mathematically derived ray-plane intersection algorithm on
https://github.com/Busedame/miniRT/blob/main/README.md#ray-object-intersection

 @note
Due to floating-point precision limitations, directly comparing a dot product
to zero can be unreliable. A small threshold (1e-6) is used to determine if the
ray is parallel to the plane. Values below this threshold are considered too
close to zero, indicating parallelism or preventing division by very small
numbers, which could lead to inaccuracies.
*/
int	ray_intersect_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane *plane,
		double *t)
{
	double	denom;
	t_vec3	difference;

	denom = vec3_dot(ray_dir, plane->normal);
	if (fabs(denom) > 1e-6)
	{
		difference = vec3_sub(plane->point_in_plane, ray_origin);
		*t = vec3_dot(difference, plane->normal) / denom;
		if (*t >= 0.0)
			return (1);
	}
	return (0);
}
