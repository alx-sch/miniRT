/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_create_shadow_ray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:54:34 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/22 20:27:38 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

t_shadow	init_shadow(t_rt *rt, t_ixr *ixr, t_vec3 ray_dir)
{
	t_shadow	shadow;

	shadow.intersection_point = vec3_add(rt->scene.cam.pos, \
	vec3_scale(ray_dir, ixr->ray_origin));
	shadow.normal = get_normal_at_point(shadow.intersection_point, \
	ixr->hit_obj);
	shadow.offset_origin = vec3_add(shadow.intersection_point, \
	vec3_scale(shadow.normal, 1e-6));
	shadow.length = vec3_length(vec3_sub(rt->scene.light.position, \
	shadow.offset_origin));
	shadow.light_dir = vec3_norm(vec3_sub(rt->scene.light.position, \
	shadow.offset_origin));
	return (shadow);
}

// t_shadow	create_shadow_ray(t_rt *rt, t_vec3 ray_dir, t_ixr *ixr, 
// 	t_obj_data *obj_data)
// {
// 	t_shadow	shadow;

// 	shadow.intersection_point = vec3_add(rt->scene.cam.pos, \
// 	vec3_scale(ray_dir, ixr->ray_origin));
// 	shadow.normal = get_normal_at_point(shadow.intersection_point, obj_data);
// 	shadow.offset_origin = vec3_add(shadow.intersection_point, \
// 	vec3_scale(shadow.normal, 1e-4));
// 	shadow.length = vec3_length(vec3_sub(rt->scene.light.position, \
// 	shadow.offset_origin));
// 	shadow.light_dir = vec3_norm(vec3_sub(rt->scene.light.position, \
// 	shadow.offset_origin));
// 	return (shadow);
// }
