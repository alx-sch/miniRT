/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_shadow_copy_objs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:23:01 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/24 17:55:37 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
All these functions makes a copy of an object, but adjusting it to do
contain data with a shadow ray (from hitpoint to light source) instead of a
regular ray (from camera to object).
*/

/**
Copies a cylinder object to contain shadow ray data instead of 
camera-to-object data.
*/
t_cylinder	copy_cylinder(t_cylinder *cyl, t_shadow *shadow)
{
	t_cylinder	new_cyl;

	new_cyl.orientation = cyl->orientation;
	new_cyl.object_type = CYLINDER;
	new_cyl.radius = cyl->radius;
	new_cyl.radius_sqrd = cyl->radius_sqrd;
	new_cyl.cap_bottom_center = cyl->cap_bottom_center;
	new_cyl.cap_bottom_normal = cyl->cap_bottom_normal;
	new_cyl.cap_top_center = cyl->cap_top_center;
	new_cyl.cap_top_normal = cyl->cap_top_normal;
	new_cyl.center = cyl->center;
	new_cyl.color = cyl->color;
	new_cyl.height = cyl->height;
	new_cyl.hex_color = cyl->hex_color;
	new_cyl.ixd.oc = vec3_sub(shadow->offset_origin, cyl->center);
	new_cyl.ixd.axis_dot_oc = vec3_dot(new_cyl.ixd.oc, cyl->orientation);
	new_cyl.ixd.c = vec3_dot(new_cyl.ixd.oc, new_cyl.ixd.oc) 
		- (new_cyl.ixd.axis_dot_oc * new_cyl.ixd.axis_dot_oc) 
		- new_cyl.radius_sqrd;
	new_cyl.ixd.cap_hit = 0;
	new_cyl.ixd.dot_to_top = vec3_dot(vec3_sub(new_cyl.cap_top_center, 
				shadow->offset_origin), new_cyl.cap_top_normal);
	new_cyl.ixd.dot_to_bottom = vec3_dot(vec3_sub(new_cyl.cap_bottom_center, 
				shadow->offset_origin), new_cyl.cap_bottom_normal);
	return (new_cyl);
}

/**
Copies a sphere object to contain shadow ray data instead of 
camera-to-object data.
*/
t_sphere	copy_sphere(t_sphere *sp, t_shadow *shadow)
{
	t_sphere	new_sp;

	new_sp.center = sp->center;
	new_sp.color = sp->color;
	new_sp.hex_color = sp->hex_color;
	new_sp.object_type = SPHERE;
	new_sp.radius = sp->radius;
	new_sp.ixd.oc = vec3_sub(shadow->light_dir, sp->center);
	new_sp.ixd.c = vec3_dot(new_sp.ixd.oc, new_sp.ixd.oc) - new_sp.radius * \
	new_sp.radius;
	return (new_sp);
}

/**
Copies a plane object to contain shadow ray data instead of 
camera-to-object data.
*/
t_plane	copy_plane(t_plane *pl, t_shadow *shadow)
{
	t_plane	new_pl;

	new_pl.color = pl->color;
	new_pl.hex_color = pl->hex_color;
	new_pl.normal = pl->normal;
	new_pl.object_type = PLANE;
	new_pl.point_in_plane = pl->point_in_plane;
	new_pl.ixd.difference = vec3_sub(pl->point_in_plane, shadow->offset_origin);
	new_pl.ixd.dot_diff_normal = vec3_dot(new_pl.ixd.difference, new_pl.normal);
	return (new_pl);
}
