/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_scene_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:13 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/19 17:37:42 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Updates an object's color based on ambient light.

 @param obj:	Pointer to the object whose color will be updated.
 @param rt:		Pointer to the main rendering structure containing scene data.
*/
static void	apply_ambient_light_to_object(t_obj *obj, t_rt *rt)
{
	float	ambi_r;
	float	ambi_g;
	float	ambi_b;
	t_color	color_in_amb;

	ambi_r = (float)rt->scene.ambi_light.color.r * rt->scene.ambi_light.ratio;
	ambi_g = (float)rt->scene.ambi_light.color.g * rt->scene.ambi_light.ratio;
	ambi_b = (float)rt->scene.ambi_light.color.b * rt->scene.ambi_light.ratio;
	color_in_amb.r = (float)obj->color.r * ambi_r / 255.0;
	color_in_amb.g = (float)obj->color.g * ambi_g / 255.0;
	color_in_amb.b = (float)obj->color.b * ambi_b / 255.0;
	obj->color_in_amb = color_to_hex(color_in_amb);
}

/**
Checks if the camera is inside a given sphere.

 @param cam_pos:	The camera position in world coordinates.
 @param obj:		Pointer to the sphere object.

 @return 			`1` if the camera is inside the sphere, `0` otherwise.
*/
static int	is_cam_inside_sphere(t_vec3 cam_pos, t_obj *obj)
{
	t_vec3	oc;
	double	dist_sq;
	double	radius_sqrd;

	oc = vec3_sub(cam_pos, obj->x.sp.center);
	dist_sq = vec3_dot(oc, oc);
	radius_sqrd = obj->x.sp.radius * obj->x.sp.radius;
	return (dist_sq < radius_sqrd);
}

/**
Checks if the camera is inside a given finite cylinder.

 @param cam_pos:	The camera position in world coordinates.
 @param obj:		Pointer to the sphere object.

 @return 			`1` if the camera is inside the cylinder, `0` otherwise.
*/
static int	is_cam_inside_cylinder(t_vec3 cam_pos, t_obj *obj)
{
	t_vec3	oc;
	double	axis_dot_oc;
	double	dist_sq;
	double	half_height;

	oc = vec3_sub(cam_pos, obj->x.cy.center);
	axis_dot_oc = vec3_dot(oc, obj->x.cy.orientation);
	dist_sq = vec3_dot(oc, oc) - (axis_dot_oc * axis_dot_oc);
	half_height = obj->x.cy.height_half;
	if (axis_dot_oc < half_height || axis_dot_oc > half_height)
		return (0);
	return (dist_sq < obj->x.cy.radius_sqrd);
}

/**
 Iterates through all objects in the scene, applies ambient lighting,
adjusts plane normals, and flags objects where the camera is inside.

 @param rt:		Double pointer to the main struct containing scene data.
*/
void	prepare_scene_objects(t_rt **rt)
{
	t_list	*current_obj;
	t_obj	*obj;
	t_vec3	cam_to_plane;

	current_obj = (*rt)->scene.objs;
	while (current_obj != NULL)
	{
		obj = (t_obj *)current_obj->content;
		apply_ambient_light_to_object(obj, *rt);
		if (obj->object_type == PLANE)
		{
			cam_to_plane = vec3_sub(obj->x.pl.point_in_plane,
					(*rt)->scene.cam.pos);
			if (vec3_dot(cam_to_plane, obj->x.pl.normal) > 0)
				obj->x.pl.normal = vec3_mult(obj->x.pl.normal, -1.0);
		}
		obj->cam_in_obj = 0;
		if (obj->object_type == SPHERE
			&& is_cam_inside_sphere((*rt)->scene.cam.pos, obj))
			obj->cam_in_obj = 1;
		else if (obj->object_type == CYLINDER
			&& is_cam_inside_cylinder((*rt)->scene.cam.pos, obj))
			obj->cam_in_obj = 1;
		current_obj = current_obj->next;
	}
}
