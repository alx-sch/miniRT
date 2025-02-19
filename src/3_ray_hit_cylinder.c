/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ray_hit_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/19 17:05:48 by aschenk          ###   ########.fr       */
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

int	ray_hit_cyl(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t);
int	ray_hit_cap_top(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t);
int	ray_hit_cap_bottom(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t);

/**
Function to check whether a given intersection point on an infinite cylinder
lies within the cylinder's finite height bounds.
 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param obj 		Pointer to the object structure.
 @param t 			The distance along the ray to the intersection point.

 @return 			`1` if the intersection point lies within the cylinder's
					height bounds;
					`0` otherwise.
*/
static int	cyl_height_check(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj,
				double t)
{
	t_vec3	intersection_point;
	t_vec3	center_to_point;
	double	projection_length;

	intersection_point = vec3_add(ray_ori, vec3_mult(ray_dir, t));
	center_to_point = vec3_sub(intersection_point, obj->x.cy.center);
	projection_length = vec3_dot(center_to_point, obj->x.cy.orientation);
	if (projection_length >= obj->x.cy.height_half * (-1)
		&& projection_length <= obj->x.cy.height_half)
		return (1);
	return (0);
}

/**
Determinse whether a ray intersects with a finite cylinder (tube)
and, if so, calculates the distance to the closest intersection point.
 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param obj 		Pointer to the object structure.
 @param t 			Pointer to store the intersection distance.

 @return 			`1` if the ray intersects with the cylinder within its
 					finite height bounds;
					`0` otherwise.
*/
int	ray_hit_cyl(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t)
{
	t_quad	qd;

	qd.axis_dot_ray = vec3_dot(ray_dir, obj->x.cy.orientation);
	qd.a = vec3_dot(ray_dir, ray_dir) - (qd.axis_dot_ray * qd.axis_dot_ray);
	qd.oc = vec3_sub(ray_ori, obj->x.cy.center);
	qd.axis_dot_oc = vec3_dot(qd.oc, obj->x.cy.orientation);
	qd.b = 2.0 * (vec3_dot(ray_dir, qd.oc)
			- (qd.axis_dot_ray * qd.axis_dot_oc));
	qd.c = vec3_dot(qd.oc, qd.oc) - (qd.axis_dot_oc * qd.axis_dot_oc)
		- obj->x.cy.radius_sqrd;
	qd.discriminant = calculate_discriminant(qd.a, qd.b, qd.c);
	if (qd.discriminant < 0)
		return (0);
	*t = calculate_entry_distance(qd.a, qd.b, qd.discriminant);
	if (*t > 0.0 && cyl_height_check(ray_ori, ray_dir, obj, *t))
		return (1);
	*t = calculate_exit_distance(qd.a, qd.b, qd.discriminant);
	if (*t > 0.0 && cyl_height_check(ray_ori, ray_dir, obj, *t))
		return (1);
	return (0);
}

/**
Function to check intersection with cylinder's top end cap.
- t_hit is the distance from the ray origin to the intersection point.
- p_hit is the intersection point.
 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param obj 		Pointer to the object structure.
 @param t 			Pointer to store the intersection distance, if valid.

 @return 			`1` if the ray intersects the cap within its radius;
					`0` otherwise.
*/
int	ray_hit_cap_top(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t)
{
	double	denominator;
	double	numerator;
	double	t_hit;
	t_vec3	p_hit;
	t_vec3	difference;

	denominator = vec3_dot(ray_dir, obj->x.cy.cap_top_normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	numerator = vec3_dot(vec3_sub(ray_ori, obj->x.cy.cap_top_center),
			obj->x.cy.cap_top_normal);
	t_hit = (-1) * (numerator / denominator);
	if (t_hit <= 0.0)
		return (0);
	p_hit = vec3_add(ray_ori, vec3_mult(ray_dir, t_hit));
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
 @param ray_ori 	The origin of the ray.
 @param ray_dir		The normalized direction vector of the ray.
 @param obj 		Pointer to the object structure.
 @param t 			Pointer to store the intersection distance, if valid.

 @return 			`1` if the ray intersects the cap within its radius;
					`0` otherwise.
*/
int	ray_hit_cap_bottom(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t)
{
	double	denominator;
	double	numerator;
	double	t_hit;
	t_vec3	p_hit;
	t_vec3	difference;

	denominator = vec3_dot(ray_dir, obj->x.cy.cap_bottom_normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	numerator = vec3_dot(vec3_sub(ray_ori, obj->x.cy.cap_bottom_center),
			obj->x.cy.cap_bottom_normal);
	t_hit = (-1) * (numerator / denominator);
	if (t_hit <= 0.0)
		return (0);
	p_hit = vec3_add(ray_ori, vec3_mult(ray_dir, t_hit));
	difference = vec3_sub(p_hit, obj->x.cy.cap_bottom_center);
	if (vec3_dot(difference, difference) <= obj->x.cy.radius_sqrd)
	{
		*t = t_hit;
		return (1);
	}
	return (0);
}
