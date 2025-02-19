/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_ambient_light_and_adj_pl_normal.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:13 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/19 12:01:54 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/* Updates an object's color based on the ambient light. */
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

/* Iterates through all objects and updates their color based
on ambient light. Also makes sure that plane normals point towards the camera
(plane's 'upside is always faces camera)*/
void	apply_ambient_light_and_adj_pl_normal(t_rt **rt)
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
		current_obj = current_obj->next;
	}
}
