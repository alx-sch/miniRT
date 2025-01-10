/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_ray_shadows_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:05:51 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/10 17:10:17 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Checks for intersection of a ray with a plane object.

If an intersection occurs and is closer than the current closest distance,
updates the closest intersection distance and the intersection color in the
provided struct.

 @param ray_dir		The direction vector of the ray.
 @param obj_data	The object data containing the plane information.
 @param ixr			Pointer to the intersection struct to update.
*/
int	shadow_check_plane_intersection(t_rt *rt, t_vec3 ray_dir, 
		t_obj_data *obj_data, t_ixr **ixr)
{
	double		t;
	t_shadow	shadow;
	t_plane		plane;

	shadow = create_shadow_ray(rt, ray_dir, *ixr, obj_data);
	plane = copy_plane(&obj_data->pl, &shadow);
	if (ray_intersect_plane(shadow.light_dir, &plane, &t) 
		&& t > 1e-4 && t < shadow.length)
		return (1);
	return (0);
}

/**
Checks for intersection of a ray with a sphere object.

If an intersection occurs and is closer than the current closest distance,
updates the closest intersection distance and the intersection color in the
provided struct.

 @param ray_dir		The direction vector of the ray.
 @param obj_data	The object data containing the sphere information.
 @param ixr			Pointer to the intersection struct to update.
*/
int	shadow_check_sphere_intersection(t_rt *rt, t_vec3 ray_dir, 
		t_obj_data *obj_data, t_ixr **ixr)
{
	double		t;
	t_shadow	shadow;
	t_sphere	sphere;

	shadow = create_shadow_ray(rt, ray_dir, *ixr, obj_data);
	sphere = copy_sphere(&obj_data->sp, &shadow);
	if (ray_intersect_sphere(ray_dir, &sphere, &t)
		&& t > 1e-4 && t < shadow.length)
		return (1);
	return (0);
}

/**
Checks for intersection of a ray with a cylinder object, including its caps.

If an intersection occurs and is closer than the current closest distance,
updates the closest intersection distance and the intersection color in the
provided struct.

 @param ray_origin	The origin of the ray.
 @param ray_dir		The direction vector of the ray.
 @param obj_data	The object data containing the cylinder information.
 @param ixr			Pointer to the intersection struct to update.

 @note
The function avoids unnecessary checks by skipping the bottom cap test if the
top cap is already marked as hit, and vice versa.
This ensures that only one cap can be marked as hit per cylinder intersection
check, as only one cap can be visible at a time in the rendering.
*/
int	shadow_check_cyl_intersection(t_rt *rt, t_vec3 ray_dir,
		t_obj_data *obj_data, t_ixr **ixr)
{
	double		t;
	t_shadow	shadow;
	t_cylinder	cylinder;

	shadow = create_shadow_ray(rt, ray_dir, *ixr, obj_data);
	cylinder = copy_cylinder(&obj_data->cy, &shadow);
	if (ray_intersect_cylinder(rt->scene.light.position, ray_dir, &cylinder, &t)
		&& t > 1e-4 && t < shadow.length)
		return (1);
	if (ray_intersect_cap_top(rt->scene.light.position,
			ray_dir, &cylinder, &t) && t > 1e-4 && t < shadow.length)
		return (1);
	if (ray_intersect_cap_bottom(rt->scene.light.position,
			ray_dir, &cylinder, &t) && t > 1e-4 && t < shadow.length)
		return (1);
	return (0);
}
