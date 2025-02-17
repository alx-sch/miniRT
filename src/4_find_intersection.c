/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_find_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:59:09 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/13 16:12:17 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Handles ray-object intersection calculations for planes, spheres, and cylinders
in the parsed object list. Determines the closest intersection distance.
*/

#include "main.h"

// IN FILE:

void	find_intersection(t_vec3 ray_dir, t_rt *rt, t_ixr *ixr);

/**
Checks for intersection of a ray with a plane object.

If an intersection occurs and is closer than the current closest distance,
updates the closest intersection distance in the provided struct.

 @param ray_dir		The direction vector of the ray.
 @param obj	The object data containing the plane information.
 @param ixr			Pointer to the intersection struct to update.
*/
static void	check_plane_intersection(t_vec3 ray_dir, t_obj *obj, t_ixr *ixr)
{
	double	t;

	if (ray_intersect_plane(ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
	}
}

/**
Checks for intersection of a ray with a sphere object.

If an intersection occurs and is closer than the current closest distance,
updates the closest intersection distance in the provided struct.

 @param ray_dir		The direction vector of the ray.
 @param obj	The object data containing the sphere information.
 @param ixr			Pointer to the intersection struct to update.
*/
static void	check_sphere_intersection(t_vec3 ray_dir, t_obj *obj, t_ixr *ixr)
{
	double	t;

	if (ray_intersect_sphere(ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
	}
}

/**
Checks for intersection of a ray with a cylinder object, including its caps.

If an intersection occurs and is closer than the current closest distance,
updates the closest intersection distance  in the provided struct.

 @param ray_origin	The origin of the ray.
 @param ray_dir		The direction vector of the ray.
 @param obj	The object data containing the cylinder information.
 @param ixr			Pointer to the intersection struct to update.

 @note
The function avoids unnecessary checks by skipping the bottom cap test if the
top cap is already marked as hit, and vice versa.
This ensures that only one cap can be marked as hit per cylinder intersection
check, as only one cap can be visible at a time in the rendering.
*/
static void	check_cyl_intersection(t_vec3 ray_origin, t_vec3 ray_dir,
		t_obj *obj, t_ixr *ixr)
{
	double		t;

	if (ray_intersect_cylinder(ray_origin, ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
	}
	if (obj->ixd.cap_hit != 2 && ray_intersect_cap_top(ray_origin,
			ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
		obj->ixd.cap_hit = 1;
	}
	if (obj->ixd.cap_hit != 1 && ray_intersect_cap_bottom(ray_origin,
			ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
		obj->ixd.cap_hit = 2;
	}
}

/**
Updates the intersection struct with the closest intersection data found in the
scene (object and distance) for a given camera ray.

 @param ray_dir 	The direction vector of the current ray.
 @param rt 			Pointer to the main program state structure.
 @param ixr 		Pointer to the intersection struct to update.

 @return 			ixr struct containing the closest intersection data.
*/
void	find_intersection(t_vec3 ray_dir, t_rt *rt, t_ixr *ixr)
{
	t_list	*current_obj;
	t_obj	*obj;

	current_obj = rt->scene.objs;
	ixr->t_hit = INFINITY;
	ixr->hit_obj = NULL;
	while (current_obj != NULL)
	{
		obj = (t_obj *)current_obj->content;
		if (obj->object_type == PLANE)
			check_plane_intersection(ray_dir, obj, ixr);
		else if (obj->object_type == SPHERE)
			check_sphere_intersection(ray_dir, obj, ixr);
		else if (obj->object_type == CYLINDER)
			check_cyl_intersection(rt->scene.cam.pos, ray_dir, obj, ixr);
		current_obj = current_obj->next;
	}
}
