/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/02 11:28:41 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
XXX
*/


#include "main.h"

// IN FILE:

int		ray_intersect_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane *plane,
			double *t);
int		ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir,
			t_sphere *sphere, double *t);

/**
Function to find the intersection of a ray with a plane.

 @param ray_origin 	The starting point of the ray (camera).
 @param ray_dir 	The normalized direction vector of the ray.
 @param plane 		Pointer to the plane structure.
 @param t 			A pointer to store the distance to the intersection point
 					(if found).

 @return 			`1` if an intersection is found in the FOV (and `t` is set
 					to the intersection distance);
					`0` if there is no intersection within the FOV (ray is
					parallel to the plane or intersection is behind the camera).

 @details
See details of the mathematically derived ray-plane intersection algorithm on
https://github.com/Busedame/miniRT/blob/main/README.md#ray-object-intersection

 @note
Due to floating-point precision limitations, directly comparing a dot product
to zero can be unreliable. A small threshold (1e-6) is used to determine if the
ray is parallel to the plane. Values below this threshold are considered too
close to zero, indicating parallelism or preventing division by very small
numbers, which could lead to inaccuracies.
*/
int	ray_intersect_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane *plane,
		double *t)
{
	double	denom;
	t_vec3	difference;

	denom = vec3_dot(ray_dir, plane->normal);
	if (fabs(denom) > 1e-6)
	{
		difference = vec3_sub(plane->point_in_plane, ray_origin);
		*t = vec3_dot(difference, plane->normal) / denom;
		if (*t >= 0.0)
			return (1);
	}
	return (0);
}

/**
Function to find the intersection of a ray with a sphere.

 @param ray_origin 	The starting point of the ray (camera).
 @param ray_dir 	The direction vector of the ray (assumed to be normalized).
 @param sphere 		Pointer to the sphere structure (contains center and radius).
 @param t 			Pointer to store the distance to the first intersection
					point (if found); could be the enter or exit point (if the
					ray is inside the sphere).

 @return 			`1` if an intersection is found (and t is set to the
					intersection distance);
					`0` if there is no intersection.

 @note 				`a = (ray_dir . ray_dir)` is 1.0 if the ray direction
					vector is normalized.
*/
int	ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir, t_sphere *sphere,
		double	*t)
{
	t_vec3	oc;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray_origin, sphere->center);
	b = 2.0 * vec3_dot(oc, ray_dir);
	c = vec3_dot(oc, oc) - (sphere->radius * sphere->radius);
	discriminant = calculate_discriminant(1.0, b, c);
	if (discriminant >= 0.0)
	{
		*t = calculate_entry_distance(1.0, b, discriminant);
		if (*t >= 0.0)
			return (1);
		*t = calculate_exit_distance(1.0, b, discriminant);
		if (*t >= 0.0)
			return (1);
	}
	return (0);
}

//############
//# CYLINDER #
//############

/**
Function to find the intersection of a ray with a cylinder.

 @param ray_origin     The starting point of the ray (camera).
 @param ray_dir        The normalized direction vector of the ray.
 @param cylinder       Pointer to the cylinder structure (contains base center,
                       axis direction, radius, and height).
 @param t              Pointer to store the distance to the intersection point
                       (if found).

 @return               `1` if an intersection is found in the FOV (and `t` is
                       set to the intersection distance);
                       `0` if there is no intersection (ray is parallel to the
                       cylinder, misses the cylinder, or intersection is behind
                       the camera).

 @note
This function assumes the cylinder is finite and defined by a central axis, a
radius, and a height. To handle precision issues, small thresholds (e.g., 1e-6)
are used for comparisons. Intersections outside the cylinder's finite height are
ignored.
*/
int	ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder,
		double *t)
{
	t_vec3	oc;
	t_vec3	cylinder_axis;
	t_vec3	ray_dir_projected;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	cylinder_axis = vec3_norm(cylinder->axis);
	oc = vec3_sub(ray_origin, cylinder->base_center);

	// Project ray direction and OC onto the plane orthogonal to the cylinder axis
	ray_dir_projected = vec3_sub(ray_dir, vec3_scale(cylinder_axis, vec3_dot(ray_dir, cylinder_axis)));
	oc = vec3_sub(oc, vec3_scale(cylinder_axis, vec3_dot(oc, cylinder_axis)));

	// Calculate quadratic coefficients
	a = vec3_dot(ray_dir_projected, ray_dir_projected);
	b = 2.0 * vec3_dot(oc, ray_dir_projected);
	c = vec3_dot(oc, oc) - (cylinder->radius * cylinder->radius);

	// Solve quadratic equation
	discriminant = calculate_discriminant(a, b, c);
	if (discriminant < 0.0)
		return (0);

	// Calculate entry and exit distances
	double	t0 = calculate_entry_distance(a, b, discriminant);
	double	t1 = calculate_exit_distance(a, b, discriminant);

	// Ensure t0 is the nearest intersection
	if (t0 > t1)
	{
		double temp = t0;
		t0 = t1;
		t1 = temp;
	}

	// Check if intersection is within the cylinder's finite height
	t_vec3 intersection_point = vec3_add(ray_origin, vec3_scale(ray_dir, t0));
	double height_check = vec3_dot(vec3_sub(intersection_point, cylinder->base_center), cylinder_axis);
	if (height_check < 0.0 || height_check > cylinder->height)
	{
		// Try the second intersection point
		intersection_point = vec3_add(ray_origin, vec3_scale(ray_dir, t1));
		height_check = vec3_dot(vec3_sub(intersection_point, cylinder->base_center), cylinder_axis);
		if (height_check < 0.0 || height_check > cylinder->height)
			return (0);
		t0 = t1;
	}

	// Ensure t is positive
	if (t0 < 0.0)
		return (0);

	*t = t0;
	return (1);
}
