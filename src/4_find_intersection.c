/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_find_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:59:09 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/18 01:20:35 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Handles ray-object intersection calculations for planes, spheres, and cylinders
in the parsed object list. Determines the closest intersection distance.
*/

#include "main.h"

// IN FILE:

void	find_intersection(t_vec3 ray_ori, t_vec3 ray_dir, t_rt *rt, t_ixr *ixr);
void	reset_cap_hits(t_rt *rt);

/**
Checks for intersection of a ray with a plane object.

Updates the intersection data in the provided `ixr` struct if an intersection
occurs that is closer than the current closest distance.

 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param obj			Pointer to the object data.
 @param ixr			Pointer to the 'intersection result' struct to update.
*/
static void	check_plane_intersection(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj,
				t_ixr *ixr)
{
	double	t;

	if (ray_intersect_plane(ray_ori, ray_dir, obj, &t) && t < ixr->t_hit)
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
static void	check_sphere_intersection(t_vec3 ray_ori, t_vec3 ray_dir,
				t_obj *obj, t_ixr *ixr)
{
	double	t;

	if (ray_intersect_sphere(ray_ori, ray_dir, obj, &t) && t < ixr->t_hit)
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
static void	check_cyl_intersection(t_vec3 ray_origin, t_vec3 ray_dir,
				t_obj *obj, t_ixr *ixr)
{
	double		t;

	if (ray_intersect_cylinder(ray_origin, ray_dir, obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
	}
	if (obj->x.cy.cap_hit != 2 && ray_intersect_cap_top(ray_origin, ray_dir,
			obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
		obj->x.cy.cap_hit = 1;
	}
	if (obj->x.cy.cap_hit != 1 && ray_intersect_cap_bottom(ray_origin, ray_dir,
			obj, &t) && t < ixr->t_hit)
	{
		ixr->t_hit = t;
		ixr->hit_obj = obj;
		obj->x.cy.cap_hit = 2;
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
void	find_intersection(t_vec3 ray_ori, t_vec3 ray_dir, t_rt *rt, t_ixr *ixr)
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
			check_plane_intersection(ray_ori, ray_dir, obj, ixr);
		else if (obj->object_type == SPHERE)
			check_sphere_intersection(ray_ori, ray_dir, obj, ixr);
		else if (obj->object_type == CYLINDER)
			check_cyl_intersection(ray_ori, ray_dir, obj, ixr);
		current_obj = current_obj->next;
	}
	if (ixr->hit_obj != NULL)
		ixr->hit_point = vec3_add(ray_ori, vec3_mult(ray_dir, ixr->t_hit));
}

/**
Resets the `cap_hit` flag for all cylinder objects in the scene.

This function ensures that any previous intersection checks with cylinder caps
are cleared before processing a new set of rays (such as camera or shadow rays).
This is important for correctly handling the intersection logic of cylinder
caps, ensuring that no cap remains marked as "hit" across multiple frames or
ray casts.

 @param rt 	Pointer to the scene data containing the objects.
*/
void	reset_cap_hits(t_rt *rt)
{
	t_list	*current_obj;
	t_obj	*obj;

	current_obj = rt->scene.objs;
	while (current_obj)
	{
		obj = (t_obj *)current_obj->content;
		if (obj->object_type == CYLINDER)
			obj->x.cy.cap_hit = 0;
		current_obj = current_obj->next;
	}
}
