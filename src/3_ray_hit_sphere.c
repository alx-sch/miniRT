/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ray_hit_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/19 17:08:38 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions to calculate the intersection of a ray with a
sphere object in 3D space.

See the README for more details on the mathematically derived ray-object
intersection algorithms used in the function below:
https://github.com/Busedame/miniRT/blob/main/README.md#ray-object-intersection
*/

#include "main.h"

// IN FILE:

int	ray_hit_sphere(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t);

/**
Function to find the intersection of a ray with a sphere.
 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param obj			Pointer to the object data.
 @param t 			A pointer to store the distance to the intersection point.

 @return 			`1` if an intersection is found (and t is set to the
					intersection distance);
					`0` if there is no intersection.

 @note 				`a = (ray_dir . ray_dir)` is 1.0 as the ray direction
					vector is normalized.
*/
int	ray_hit_sphere(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t)
{
	t_quad	qd;

	qd.oc = vec3_sub(ray_ori, obj->x.sp.center);
	qd.b = 2.0 * vec3_dot(qd.oc, ray_dir);
	qd.c = vec3_dot(qd.oc, qd.oc) - (obj->x.sp.radius * obj->x.sp.radius);
	qd.discriminant = calculate_discriminant(1.0, qd.b, qd.c);
	if (qd.discriminant < 0.0)
		return (0);
	*t = calculate_entry_distance(1.0, qd.b, qd.discriminant);
	if (*t > 0.0)
		return (1);
	*t = calculate_exit_distance(1.0, qd.b, qd.discriminant);
	if (*t > 0.0)
		return (1);
	return (0);
}
