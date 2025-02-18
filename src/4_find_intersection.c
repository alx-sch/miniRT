/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_find_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:59:09 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/18 08:02:56 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Handles ray-object intersection calculations for planes, spheres, and cylinders
in the parsed object list. Determines the closest intersection distance.
*/

#include "main.h"

// IN FILE:

void	find_ix(t_vec3 ray_ori, t_vec3 ray_dir, t_rt *rt, t_ixr *ixr);

/**
Checks for intersection of a ray with a plane object.

Updates the intersection data in the provided `ixr` struct if an intersection
occurs that is closer than the current closest distance.

 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param obj			Pointer to the object data.
 @param ixr			Pointer to the 'intersection result' struct to update.
*/
static void	plane_ix(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, t_ixr *ixr)
{
	double	t;

	if (ray_hit_plane(ray_ori, ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
	}
}

/**
Checks for intersection of a ray with a sphere object.

Updates the intersection data in the provided `ixr` struct if an intersection
occurs that is closer than the current closest distance.

 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param obj			Pointer to the object data.
 @param ixr			Pointer to the 'intersection result' struct to update.
*/
static void	sphere_ix(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, t_ixr *ixr)
{
	double	t;

	if (ray_hit_sphere(ray_ori, ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
	}
}

/**
Checks for intersection of a ray with a cylinder object, including its caps.

Updates the intersection data in the provided `ixr` struct if an intersection
occurs that is closer than the current closest distance.

 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param obj			Pointer to the object data.
 @param ixr			Pointer to the 'intersection result' struct to update.

 @note
The function avoids unnecessary checks by skipping the bottom cap test if the
top cap is already marked as hit, and vice versa.
This ensures that only one cap can be marked as hit per cylinder intersection
check, as only one cap can be visible at a time in the rendering.
*/
static void	cyl_ix(t_vec3 ray_origin, t_vec3 ray_dir, t_obj *obj, t_ixr *ixr)
{
	double		t;

	if (ray_hit_cyl(ray_origin, ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
	}
	if (ray_hit_cap_top(ray_origin, ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
	}
	if (ray_hit_cap_bottom(ray_origin, ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
	}
}

/**
Updates the intersection struct with the closest intersection data found in the
scene (object and distance) for a given camera ray.

 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param rt 			Pointer to rt struct containing the object data.
 @param ixr 		Pointer to the 'intersection result' struct to update.

 @return 			ixr struct containing the closest intersection data.
*/
void	find_ix(t_vec3 ray_ori, t_vec3 ray_dir, t_rt *rt, t_ixr *ixr)
{
	t_list	*current_obj;
	t_obj	*obj;

	current_obj = rt->scene.objs;
	ixr->hit_obj = NULL;
	ixr->t_hit = INFINITY;
	while (current_obj)
	{
		obj = (t_obj *)current_obj->content;
		if (obj->object_type == PLANE)
			plane_ix(ray_ori, ray_dir, obj, ixr);
		else if (obj->object_type == SPHERE)
			sphere_ix(ray_ori, ray_dir, obj, ixr);
		else if (obj->object_type == CYLINDER)
			cyl_ix(ray_ori, ray_dir, obj, ixr);
		current_obj = current_obj->next;
	}
	if (ixr->hit_obj != NULL)
		ixr->hit_point = vec3_add(ray_ori, vec3_mult(ray_dir, ixr->t_hit));
}
