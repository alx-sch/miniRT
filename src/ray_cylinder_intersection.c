/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/03 13:39:32 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "main.h"

// IN FILE:

int			ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir,
				t_cylinder *cylinder, double *t);

/**
Function to calculate the coefficients of the quadratic equation for
the intersection of a ray with a cylinder.

 @param cyl 		Pointer to the cylinder structure.
 @param ray_dir 	The normalized direction vector of the ray.
 @param oc 			The vector from the ray origin to the cylinder center.

 @return			None. The function modifies the cylinder's `quadratic`
 					structure to store the calculated coefficients and the
					discriminante.
*/
static void	compute_cylinder_quadratic_coefficients(t_cylinder *cyl,
			t_vec3 ray_dir)
{
	double	axis_dot_ray;

	axis_dot_ray = vec3_dot(ray_dir, cyl->orientation);
	cyl->ixd.a = vec3_dot(ray_dir, ray_dir)
		- (axis_dot_ray * axis_dot_ray);
	cyl->ixd.b = 2 * (vec3_dot(cyl->ixd.oc, ray_dir)
			- (cyl->ixd.axis_dot_oc * axis_dot_ray));
	cyl->ixd.discriminant = calculate_discriminant(cyl->ixd.a, cyl->ixd.b,
			cyl->ixd.c);
}

// /**
// Function to check if a point along a ray's intersection with a cylinder is
// within the cylinder's height bounds. It is assumed that the height is centered
// at the cylinder's center.

//  @param ray_origin 	The origin of the ray.
//  @param ray_dir		The normalized direction vector of the ray.
//  @param t 			The intersection distance along the ray.
//  @param cylinder 	The cylinder structure containing height information.

//  @return 			`1` if the intersection point is within the height bounds
// 					of the cylinder;
// 					`0` otherwise.
// */
static int	check_cylinder_height(t_vec3 ray_origin, t_vec3 ray_dir, double t,
		t_cylinder *cylinder)
{
	t_vec3	intersection_point;
	t_vec3	center_to_point;
	double	projection_length;
	double	half_height;

	// Calculate the intersection point
	intersection_point = vec3_add(ray_origin, vec3_mult(ray_dir, t));

	// Calculate the vector from the cylinder center to the intersection point
	center_to_point = vec3_sub(intersection_point, cylinder->center);

	// Project this vector onto the cylinder's axis
	projection_length = vec3_dot(center_to_point, cylinder->orientation);

	// Check if the projection length is within the height bounds
	half_height = cylinder->height / 2.0;
	if (projection_length >= -half_height && projection_length <= half_height)
		return (1);
	return (0);
}


int	ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir,
		t_cylinder *cylinder, double *t)
{
	compute_cylinder_quadratic_coefficients(cylinder, ray_dir);
	if (cylinder->ixd.discriminant < 0)
		return (0);
	*t = calculate_entry_distance(cylinder->ixd.a, cylinder->ixd.b,
			cylinder->ixd.discriminant);
	if (*t >= 0.0 && check_cylinder_height(ray_origin, ray_dir, *t, cylinder))
	{
		//print_ray_cylinder_intersection(ray_origin, ray_dir, cylinder, *t);
		return (1);
	}
	*t = calculate_exit_distance(cylinder->ixd.a, cylinder->ixd.b,
			cylinder->ixd.discriminant);
	if (*t >= 0.0 && check_cylinder_height(ray_origin, ray_dir, *t, cylinder))
	{
		//print_ray_cylinder_intersection(ray_origin, ray_dir, cylinder, *t);
		return (1);
	}
	return (0);
}


/**
Function to find the intersection of a ray with a cylinder.

 @param ray_origin 	The starting point of the ray.
 @param ray_dir 	The direction vector of the ray (assumed to be normalized).
 @param cylinder 	Pointer to the cylinder structure.
 @param t 			Pointer to store the distance to the first intersection
					point (if found); could be the enter or exit point (if the
					ray starts inside the cylibder).

 @return            `1` if an intersection is found (and `t` is set to the
					intersection distance);
					`0` if there is no intersection.

 @note
This function does not take into account:
- The height bounds of the cylinder
- Intersection with the cylinder's end caps
*/
// int	ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir,
// 		t_cylinder *cylinder, double *t)
// {
// 	t_vec3	oc;

// 	oc = vec3_sub(ray_origin, cylinder->center);
// 	compute_cylinder_quadratic_coefficients(cylinder, ray_dir, oc);
// 	if (cylinder->quadratic.discriminant < 0)
// 		return (0);
// 	*t = calculate_entry_distance(cylinder->quadratic.a, cylinder->quadratic.b,
// 			cylinder->quadratic.discriminant);
// 	if (*t >= 0.0)
// 		return (1);
// 	*t = calculate_exit_distance(cylinder->quadratic.a, cylinder->quadratic.b,
// 			cylinder->quadratic.discriminant);
// 	if (*t >= 0.0)
// 		return (1);
// 	return (0);
// }
