/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_shadow_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:05:51 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/22 20:41:34 by nholbroo         ###   ########.fr       */
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
		t_plane plane, t_ixr **ixr)
{
	double		t;

	if (ray_intersect_plane(ray_dir, &plane, &t) 
		&& t > 1e-6 && t < (*ixr)->shadow.length)
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
		t_sphere sp, t_ixr **ixr)
{
	double		t;

	if (ray_intersect_sphere(ray_dir, &sp, &t)
		&& t > 1e-6 && t < (*ixr)->shadow.length)
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
		t_cylinder cyl, t_ixr **ixr)
{
	double		t;

	if (ray_intersect_cylinder((*ixr)->shadow.offset_origin, ray_dir, \
		&cyl, &t) && t > 1e-6 && t < (*ixr)->shadow.length)
		return (1);
	if (ray_intersect_cap_top((*ixr)->shadow.offset_origin, ray_dir, \
		&cyl, &t) && t > 1e-6 && t < (*ixr)->shadow.length)
		return (1);
	if (ray_intersect_cap_bottom((*ixr)->shadow.offset_origin, ray_dir, \
		&cyl, &t) && t > 1e-6 && t < (*ixr)->shadow.length)
		return (1);
	return (0);
}

int	is_ray_in_shadow(t_vec3 ray_dir, t_rt *rt, t_ixr *ixr)
{
	t_list		*current_obj;
	t_obj_data	*obj_data;

	current_obj = rt->scene.objs;
	while (current_obj != NULL)
	{
		obj_data = (t_obj_data *)current_obj->content;
		if (obj_data->pl.object_type == PLANE)
		{
			shadow_check_plane_intersection(rt, ray_dir, \
			copy_plane(&obj_data->pl, &ixr->shadow), &ixr);
		}
		else if (obj_data->sp.object_type == SPHERE)
		{
			shadow_check_sphere_intersection(rt, ray_dir, \
			copy_sphere(&obj_data->sp, &ixr->shadow), &ixr);
		}
		else if (obj_data->cy.object_type == CYLINDER)
		{
			shadow_check_cyl_intersection(rt, ray_dir, \
			copy_cylinder(&obj_data->cy, &ixr->shadow), &ixr);
		}
		current_obj = current_obj->next;
	}
	return (0);
}
