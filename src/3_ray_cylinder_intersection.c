/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ray_cylinder_intersection.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/15 10:44:38 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains functions to calculate the intersection of a ray with a
cylinder object in 3D space. As a cylinder is a combination of a tube and
two end caps, there are three separate functions to check for intersection with
each part.

See the README for more details on the mathematically derived ray-object
intersection algorithms used in the functions below:
https://github.com/Busedame/miniRT/blob/main/README.md#ray-object-intersection
*/

#include "main.h"

// IN FILE:

int		ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir,
			t_obj *obj, double *t);
int		ray_intersect_cap_top(t_vec3 ray_origin, t_vec3 ray_dir,
			t_obj *obj, double *t);
int		ray_intersect_cap_bottom(t_vec3 ray_origin, t_vec3 ray_dir,
			t_obj *obj, double *t);

/**
Function to check whether a given intersection point on an infinite cylinder
lies within the cylinder's finite height bounds.

 @param ray_origin 	The origin of the ray in 3D space.
 @param ray_dir 	The normalized direction vector of the ray.
 @param t 			The distance along the ray to the intersection point.
 @param cylinder 	Pointer to the cylinder structure.

 @return 			`1` if the intersection point lies within the cylinder's
					height bounds;
					`0` otherwise.
*/
static int	check_cylinder_height(t_vec3 ray_origin, t_vec3 ray_dir,
		t_obj *obj, double t)
{
	t_vec3	intersection_point;
	t_vec3	center_to_point;
	double	projection_length;
	double	half_height;

	intersection_point = vec3_add(ray_origin, vec3_mult(ray_dir, t));
	center_to_point = vec3_sub(intersection_point, obj->x.cy.center);
	projection_length = vec3_dot(center_to_point, obj->x.cy.orientation);
	half_height = obj->x.cy.height / 2.0;
	if (projection_length >= -half_height && projection_length <= half_height)
		return (1);
	return (0);
}

/**
Function to determine whether a ray intersects with a finite cylinder (tube)
and, if so, calculate the distance to the closest intersection point.

 @param ray_origin 	The origin of the ray in 3D space.
 @param ray_dir 	The normalized direction vector of the ray.
 @param cylinder 	Pointer to the cylinder structure.
 @param t 			Pointer to store the distance to the first intersection
					point (if found); could be the entry or exit point
					(if the ray starts inside the object ).

 @return 			`1` if the ray intersects with the cylinder within its
 					finite height bounds;
					`0` otherwise.
*/
int	ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir,
		t_obj *obj, double *t)
{
	double	axis_dot_ray;
	double	a;
	double	b;
	double	discriminant;

	axis_dot_ray = vec3_dot(ray_dir, obj->x.cy.orientation);
	a = vec3_dot(ray_dir, ray_dir) - (axis_dot_ray * axis_dot_ray);
	b = 2 * (vec3_dot(obj->ixd.oc, ray_dir)
			- (obj->ixd.axis_dot_oc * axis_dot_ray));
	discriminant = calculate_discriminant(a, b, obj->ixd.c);
	if (discriminant < 0)
		return (0);
	*t = calculate_entry_distance(a, b, discriminant);
	if (*t > 0.0 && check_cylinder_height(ray_origin, ray_dir, obj, *t))
		return (1);
	*t = calculate_exit_distance(a, b, discriminant);
	if (*t > 0.0 && check_cylinder_height(ray_origin, ray_dir, obj, *t))
		return (1);
	return (0);
}

/**
Function to check intersection with cylinder's top end cap.
- t_hit is the distance from the ray origin to the intersection point.
- p_hit is the intersection point.

 @param ray_origin 	The origin of the ray.
 @param ray_dir 	The normalized direction vector of the ray.
 @param cylinder 	Pointer to the cylinder structure.
 @param t 			Pointer to store the intersection distance if valid.

 @return 			`1` if the ray intersects the cap within its radius;
					`0` otherwise.
*/
int	ray_intersect_cap_top(t_vec3 ray_origin, t_vec3 ray_dir,
		t_obj *obj, double *t)
{
	double	denominator;
	double	numerator;
	double	t_hit;
	t_vec3	p_hit;
	t_vec3	difference;

	denominator = vec3_dot(ray_dir, obj->x.cy.cap_top_normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	numerator = vec3_dot(vec3_sub(ray_origin, obj->x.cy.cap_top_center),
			obj->x.cy.cap_top_normal);
	t_hit = (-1) * (numerator / denominator);
	if (t_hit <= 0.0)
		return (0);
	p_hit = vec3_add(ray_origin, vec3_mult(ray_dir, t_hit));
	difference = vec3_sub(p_hit, obj->x.cy.cap_top_center);
	if (vec3_dot(difference, difference) <= obj->x.cy.radius_sqrd)
	{
		*t = t_hit;
		return (1);
	}
	return (0);
}

/**
Function to check intersection with cylinder's bottom end cap.
- t_hit is the distance from the ray origin to the intersection point.
- p_hit is the intersection point.

 @param ray_origin 	The origin of the ray.
 @param ray_dir 	The normalized direction vector of the ray.
 @param cylinder 	Pointer to the cylinder structure.
 @param t 			Pointer to store the intersection distance if valid.

 @return 			`1` if the ray intersects the cap within its radius;
					`0` otherwise.
*/
int	ray_intersect_cap_bottom(t_vec3 ray_origin, t_vec3 ray_dir,
		t_obj *obj, double *t)
{
	double	denominator;
	double	numerator;
	double	t_hit;
	t_vec3	p_hit;
	t_vec3	difference;

	denominator = vec3_dot(ray_dir, obj->x.cy.cap_bottom_normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	numerator = vec3_dot(vec3_sub(ray_origin, obj->x.cy.cap_bottom_center),
			obj->x.cy.cap_bottom_normal);
	t_hit = (-1) * (numerator / denominator);
	if (t_hit <= 0.0)
		return (0);
	p_hit = vec3_add(ray_origin, vec3_mult(ray_dir, t_hit));
	difference = vec3_sub(p_hit, obj->x.cy.cap_bottom_center);
	if (vec3_dot(difference, difference) <= obj->x.cy.radius_sqrd)
	{
		*t = t_hit;
		return (1);
	}
	return (0);
}
