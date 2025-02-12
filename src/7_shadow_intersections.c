/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_shadow_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:05:51 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/12 23:54:20 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Checks for intersection of a shadow ray with a plane object.

Returns 1 if there was an intersection.
Returns 0 if there was no intersection
*/
int	shadow_check_plane_intersection(t_rt *rt, t_vec3 ray_dir,
		t_plane plane, t_ixr **ixr)
{
	double		t;

	if (ray_intersect_plane(ray_dir, &plane, &t)
		&& t > 1e-3 && t < (*ixr)->shadow.length && !plane.hit)
		return (1);
	return (0);
}

/**
Checks for intersection of a shadow ray with a sphere object.

Returns 1 if there was an intersection.
Returns 0 if there was no intersection
*/
int	shadow_check_sphere_intersection(t_rt *rt, t_vec3 ray_dir,
		t_sphere sp, t_ixr **ixr)
{
	double		t;

	if (ray_intersect_sphere(ray_dir, &sp, &t)
		&& t > 1e-3 && t < (*ixr)->shadow.length && !sp.hit)
		return (1);
	return (0);
}

/**
Checks for intersection of a shadow ray with a cylinder.

Returns 1 if there was an intersection.
Returns 0 if there was no intersection
*/
int	shadow_check_cyl_intersection(t_rt *rt, t_vec3 ray_dir,
		t_cylinder cyl, t_ixr **ixr)
{
	double		t;

	if (ray_intersect_cylinder((*ixr)->shadow.offset_origin, ray_dir, \
		&cyl, &t) && t > 1e-3 && t < (*ixr)->shadow.length && !cyl.hit)
		return (1);
	if (ray_intersect_cap_top((*ixr)->shadow.offset_origin, ray_dir, \
		&cyl, &t) && t > 1e-3 && t < (*ixr)->shadow.length && !cyl.hit)
		return (1);
	if (ray_intersect_cap_bottom((*ixr)->shadow.offset_origin, ray_dir, \
		&cyl, &t) && t > 1e-3 && t < (*ixr)->shadow.length && !cyl.hit)
		return (1);
	return (0);
}

/**
Checks if there are any objects between the hitpoint (the hit object) and the
light source. If there is - this would mean the point is in shadow.

Returns 1 if there was an intersection.
Returns 0 if there was no intersection
*/
static int	is_object_blocking_light(t_rt *rt, t_obj *obj, t_ixr *ixr)
{
	if (obj->pl.object_type == PLANE)
	{
		if (shadow_check_plane_intersection(rt, ixr->shadow.light_dir, \
		copy_plane(&obj->pl, &ixr->shadow), &ixr))
			return (1);
	}
	else if (obj->sp.object_type == SPHERE)
	{
		if (shadow_check_sphere_intersection(rt, ixr->shadow.light_dir, \
		copy_sphere(&obj->sp, &ixr->shadow), &ixr))
			return (1);
	}
	else if (obj->cy.object_type == CYLINDER)
	{
		if (shadow_check_cyl_intersection(rt, ixr->shadow.light_dir, \
		copy_cylinder(&obj->cy, &ixr->shadow), &ixr))
			return (1);
	}
	return (0);
}

/**
Iterates through all the objects in the scene, and checks if there is an
intersection between the hit object and the light source.

Returns 1 if there was an intersection.
Returns 0 if there was no intersection
*/
int	is_ray_in_shadow(t_rt *rt, t_ixr *ixr)
{
	t_list	*current_obj;
	t_obj	*obj;

	current_obj = rt->scene.objs;
	while (current_obj != NULL)
	{
		obj = (t_obj *)current_obj->content;
		if (is_object_blocking_light(rt, obj, ixr))
			return (1);
		current_obj = current_obj->next;
	}
	return (0);
}
