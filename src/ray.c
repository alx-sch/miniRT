/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/29 16:12:06 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// IN FILE:

int		ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir,
			t_sphere *sphere, double *t);
t_vec3	compute_ray_direction(int x, int y, t_cam cam);


/**
Function to find the intersection of a ray with a sphere.

 @param ray_origin 	The starting point of the ray (3D vector).
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

/**
Function to find the intersection of a ray with a plane.

 @param ray_origin 	The starting point of the ray (3D vector).
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

//############
//# CYLINDER #
//############

/**
Function to compute the ray direction for a given pixel in a camera's view,
considering the camera's field of view (FOV) and the aspect ratio of the screen.

This function calculates the direction of the ray in camera space that passes
through a specific pixel on the screen (given by coordinates `x`, `y`).
It accounts for the camera's FOV, the aspect ratio of the screen, and normalizes
the direction vector so that it has a unit length.

 @param x		The x-coordinate of the pixel on the screen (horizontal axis).
 @param y 		The y-coordinate of the pixel on the screen (vertical axis).
 @param cam 	The camera object containing the FOV.

 @return		The normalized direction vector of the ray passing through
				the pixel, in camera space.

 @details
The function works by first converting the pixel coordinates `(x, y)` to
normalized device coordinates in the range of -1 to 1.

This is done by the following steps:
1. Aspect Ratio:	The `aspect_ratio` is calculated by dividing the screen width
					by the screen height. This ensures that the ray direction
					accounts for the shape of the screen.
2. Scaling Factor:	The scaling factor (`scale`) is derived from the cam's FOV.
					The FOV is converted from degrees to radians and then the
					tangent of half the FOV angle is computed. This factor
					scales the pixel's coordinates to match the cam's FOV.
3. Normalized Device Coordinates:	The screen coordinates `(x, y)` are
   transformed into normalized device coordinates (`norm_x`, `norm_y`), where
   the center of the screen is mapped to `(0, 0)` and the edges are mapped to
   `-1` and `1`.
   - `norm_x`: The normalized x-coord., accounting for the aspect ratio and FOV.
   - `norm_y`: The normalized y-coord., scaled by the FOV.
4. Ray Direction:	The `ray_dir` is calculated in camera space as a vector
					`(norm_x, norm_y, 1.0)`. The ray points along the camera's
					forward axis (`z = 1.0`).
5. Normalization:	The `ray_dir` vector is then normalized to ensure it has
					unit length (magnitude = 1).

############################
## STEP-BY-STEP BREAKDOWN ##
############################

*******************************************
** Intermediate Calculations for Scaling **
*******************************************

float fov_half_deg = cam.fov * 0.5; // Half of the field of view in degrees
float fov_half_rad = fov_half_deg * M_PI / 180.0; // Convert degrees to radians
scale = tan(fov_half_rad);  // Calculate the tangent of the half FOV angle

** Halving the Field of View:**
cam.fov * 0.5: The FOV is halved because, in perspective projection, the tangent
function needs the angle from the center of the view to the edge,
not the full angle. This is also known as the vertical half-angle.

** Converting Degrees to Radians:**
M_PI / 180.0: Since trigonometric functions like tan in C/C++ work with radians,
we need to convert the angle from degrees to radians. Multiplying by
π/180 achieves this conversion.

**Tangent Calculation:**
tan(fov_half_rad): Calculates the tangent of the half-angle.
This value represents the relationship between the vertical size of the view at
a certain depth and the distance from the camera. In essence, it defines the
scale factor for mapping the normalized screen coordinates to world coordinates.


*******************************************
** Intermediate Calculations for x and y **
*******************************************

float x_centered = x + 0.5;	// Center of the pixel
float x_normalized = (2.0 * x_centered / WINDOW_W) - 1.0; // Map to [-1, 1]
float x_aspect_corrected = x_normalized * aspect_ratio; // Adjust for aspect r.
norm_x = x_aspect_corrected * scale; // Apply scaling

float y_centered = y + 0.5; // Center of the pixel
float y_normalized = 1.0 - (2.0 * y_centered / WINDOW_H); //	Map [-1, 1] and
																invert Y
norm_y = y_normalized * scale; // Apply scaling

**Centering Pixels:**
`x + 0.5` and `y + 0.5`: This centers the calculation on the pixel's middle
point rather than its corner, improving precision when mapping to continuous
coordinates.

**Normalization to [-1, 1]:**
`(2.0 * (x_centered / WINDOW_W)) - 1.0`: Transforms the range from [0, WINDOW_W]
to [-1, 1]. This standardizes the horizontal coordinates in the NDC.

Similarly,` 1.0 - (2.0 * (y_centered / WINDOW_H))` maps vertical coordinates
from [0, WINDOW_H] to [-1, 1], with the Y-axis inverted so that the top of the
screen is positive.

**Aspect Ratio Correction:**
`x_normalized * aspect_ratio`: Adjusts the X coordinate based on the screen's
aspect ratio to ensure the output doesn't appear stretched.
*/
t_vec3	compute_ray_direction(int x, int y, t_cam cam)
{
	double	aspect_ratio;
	double	scale;
	double	norm_x;
	double	norm_y;
	t_vec3	ray_dir;

	aspect_ratio = (double)WINDOW_W / (double)WINDOW_H;
	scale = tan((cam.fov * 0.5) * M_PI / 180.0);
	norm_x = (2.0 * (x + 0.5) / WINDOW_W - 1.0) * aspect_ratio * scale;
	norm_y = (1.0 - 2.0 * (y + 0.5) / WINDOW_H) * scale;
	ray_dir.x = norm_x;
	ray_dir.y = norm_y;
	ray_dir.z = 1.0;
	return (vec3_norm(ray_dir));
}
