/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_create_shadow_ray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:54:34 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/12 18:46:58 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Calculates the normal vector of a cylinder.
-> If the point lies on the curved side of the cylinder, the normal is
perpendicular to the axis and points outward.
-> If the point is on one of the cylinder's caps, the normal is the same as
the cap's orientation.
*/
t_vec3	calculate_cylinder_normal(t_vec3 intersection_point,
	t_obj_data *obj_data)
{
	t_cylinder	*cy;
	t_vec3		point_on_axis;
	t_vec3		normal;
	double		projection_length;

	cy = &obj_data->cy;
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

/*
Finds the normal vector for the hit object.
Normal vector: A vector that is perpendicular to the surface of an object
at a given point.
PLANE:
For a plane, the normal vector is constant everywhere because a plane is flat
and infinite. The function simply returns the predefined normal vector of the
plane (obj_data->pl.normal).
SPHERE:
For a sphere, the normal vector at a point on its surface is the vector
pointing outward from the sphere's center to the given point on the surface.
CYLINDER:
For a cylinder, the calculation of the normal vector is more complex and depends
on the shape's geometry. The function calculate_cylinder_normal is responsible
for computing the normal vector considering the curvature and orientation of
the cylinder.
*/
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

/**
Initializes a shadow ray.
@param intersection_point Finds the intersection point (the coordinates of the
hitpoint).
@param normal Finds the normal vector of the hit object (a vector that is
perpendicular to the object at the hitpoint).
@param offset_origin Finds the offset origin (the intersection point, but with
a small tweak to avoid self-shadowing/shadow acne).
@param length Finds the distance from the hitpoint (offset origin) to the
light source.
@param light_dir Finds the direction from the hitpoint to the light source.
*/
t_shadow	init_shadow(t_rt *rt, t_ixr *ixr, t_vec3 ray_dir)
{
	t_shadow	shadow;

	shadow.intersection_point = vec3_add(rt->scene.cam.pos, \
	vec3_scale(ray_dir, ixr->t_closest));
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
