/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_ray_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:23:12 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/10 16:56:35 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
			if (shadow_check_plane_intersection(rt, ray_dir, obj_data, &ixr))
				return (1);
		}
		else if (obj_data->sp.object_type == SPHERE)
		{
			if (shadow_check_sphere_intersection(rt, ray_dir, obj_data, &ixr))
				return (1);
		}
		else if (obj_data->cy.object_type == CYLINDER)
		{
			if (shadow_check_cyl_intersection(rt, ray_dir, obj_data, &ixr))
				return (1);
		}
		current_obj = current_obj->next;
	}
	return (0);
}

// Initially set color mixed with ambient light.
// Later on, if it's NOT in shadow, do further operations.
void	modify_color(t_vec3 ray_dir, t_rt *rt, t_ixr *ixr)
{
	if (is_ray_in_shadow(ray_dir, rt, ixr))
		ixr->ixn_color = 0;
}

t_vec3	calculate_cylinder_normal(t_vec3 intersection_point, 
	t_obj_data *obj_data)
{
	t_cylinder	*cy;
	t_vec3		point_on_axis;
	t_vec3		normal;
	double		projection_length;

	cy = &obj_data->cy;
	cy->orientation = vec3_norm(cy->orientation);
	projection_length = vec3_dot(vec3_sub(intersection_point, cy->center), 
			cy->orientation);
	if (projection_length >= 1e-6 && projection_length < cy->height)
	{
		point_on_axis = vec3_add(cy->center, 
				vec3_scale(cy->orientation, projection_length));
		normal = vec3_sub(intersection_point, point_on_axis);
		return (vec3_norm(normal));
	}
	if (projection_length >= cy->height - 1e-6)
		return (cy->cap_top_normal);
	if (projection_length <= 1e-6)
		return (cy->cap_bottom_normal);
	return ((t_vec3){0, 0, 0});
}

t_vec3	get_normal_at_point(t_vec3 point, t_obj_data *obj_data)
{
	if (obj_data->pl.object_type == PLANE)
		return (obj_data->pl.normal);
	else if (obj_data->sp.object_type == SPHERE)
		return (vec3_norm(vec3_sub(point, obj_data->sp.center)));
	else if (obj_data->cy.object_type == CYLINDER)
		return (calculate_cylinder_normal(point, obj_data));
	return ((t_vec3){0, 0, 0});
}

// NB -- length of vector from hitpoint to light source!!
// IF LIGHT SOURCE IS CLOSER TO HITPOINT THAN THE OBJECT INTERSECTION, THEN
// IT IS NOT IN SHADOW.
// CHECK IF ALL THE FUNCTIONS IN THIS FILE ACTUALLY CALCULATES CORRECTLY
// SEND ONE RAY AS A TEST!
t_shadow	create_shadow_ray(t_rt *rt, t_vec3 ray_dir, t_ixr *ixr, 
	t_obj_data *obj_data)
{
	t_shadow	shadow;

	shadow.intersection_point = vec3_add(rt->scene.cam.pos, \
	vec3_scale(ray_dir, ixr->ray_origin));
	shadow.normal = get_normal_at_point(shadow.intersection_point, obj_data);
	shadow.offset_origin = vec3_add(shadow.intersection_point, \
	vec3_scale(shadow.normal, 1e-3));
	shadow.length = vec3_length(vec3_sub(rt->scene.light.position, \
	shadow.offset_origin));
	shadow.light_dir = vec3_norm(vec3_sub(rt->scene.light.position, \
	shadow.offset_origin));
	return (shadow);
}
