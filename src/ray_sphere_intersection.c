/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/03 13:40:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "main.h"

// IN FILE:

int		ray_intersect_sphere(t_vec3 ray_dir, t_sphere *sphere, double *t);

/**
Function to find the intersection of a ray with a sphere.

 @param ray_origin 	The starting point of the ray (3D vector).
 @param ray_dir 	The direction vector of the ray (assumed to be normalized).
 @param sphere 		Pointer to the sphere structure (contains center and radius).
 @param t 			Pointer to store the distance to the first intersection
					point (if found); could be the enter or exit point (if the
					ray starts inside the sphere).

 @return 			`1` if an intersection is found (and t is set to the
					intersection distance);
					`0` if there is no intersection.

 @note 				`a = (ray_dir . ray_dir)` is 1.0 if the ray direction
					vector is normalized.
*/
int	ray_intersect_sphere(t_vec3 ray_dir, t_sphere *sphere, double *t)
{
	sphere->ixd.b = 2.0 * vec3_dot(sphere->ixd.oc, ray_dir);
	sphere->ixd.discriminant = calculate_discriminant(1.0, sphere->ixd.b,
			sphere->ixd.c);
	if (sphere->ixd.discriminant < 0.0)
		return (0);
	*t = calculate_entry_distance(1.0, sphere->ixd.b, sphere->ixd.discriminant);
	if (*t >= 0.0)
		return (1);
	*t = calculate_exit_distance(1.0, sphere->ixd.b, sphere->ixd.discriminant);
	if (*t >= 0.0)
		return (1);
	return (0);
}
