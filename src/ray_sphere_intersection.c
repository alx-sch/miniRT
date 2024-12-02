/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/02 20:44:26 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "main.h"

// IN FILE:

int		ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir,
			t_sphere *sphere, double *t);

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
int	ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir, t_sphere *sphere,
		double	*t)
{
	t_vec3	oc;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray_origin, sphere->center);
	b = 2.0 * vec3_dot(oc, ray_dir);
	c = vec3_dot(oc, oc) - (sphere->radius * sphere->radius);
	discriminant = calculate_discriminant(1.0, b, c);
	if (discriminant < 0.0)
		return (0);
	*t = calculate_entry_distance(1.0, b, discriminant);
	if (*t >= 0.0)
		return (1);
	*t = calculate_exit_distance(1.0, b, discriminant);
	if (*t >= 0.0)
		return (1);
	return (0);
}
