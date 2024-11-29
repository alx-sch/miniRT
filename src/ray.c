/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/29 10:58:44 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// IN FILE:

int		ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir,
			t_sphere *sphere, double *t);
t_vec3	compute_ray_direction(int x, int y, t_cam cam);

/**
Calculates the discriminant of a quadratic equation `ax^2 + bx + c = 0`, which
solves into `x = (-b ± sqrt(b^2 - 4ac)) / 2a`.

The discriminant `D = b^2 - 4ac` tells us:
- if `D > 0`, there are two real roots (the ray intersects the sphere at two
  points).
- if `D = 0`, there is one real root (the ray is tangent to the sphere, touching
  it at one point).
- if `D < 0`, there are no real roots (the ray does not intersect the sphere).

 @param a 	The coefficient of the quadratic term in quadratic equation.
 @param b 	The coefficient of the linear term in quadratic equation.
 @param c 	The constant term in quadratic equation.

 @return 	The discriminant of the quadratic equation.

 @details
 Ray equation:
	`P(t) = ray_origin + t * ray_dir`, where:
- `t` is the scaling factor for the direction vector; if the direction vector
  is normalized, `t` is the distance from origin to the point on the ray.
- `P(t)` is the position of a point on the ray at a distance `t` from
  the origin (3d vector).
- `ray_origin` is the origin of the ray (3d vector).
- `ray_dir` is the direction of the ray (3d vector).

Sphere equation:
	`||P-C||^2 = r^2`, where:
- `P` is a point on the sphere's surface (3d vector).
- `C` is the center of the sphere (3d vector).
- ||P-C|| is the distance between the point P and the center C.
- `r` is the radius of the sphere.

Substitute the ray equation into the sphere equation (ray-sphere intersection):
	`||ray_origin + t * ray_dir - C||^2 = r^2`, where:
- `t` is the unknown variable.
- `ray_origin` is the origin of the ray (known).
- `ray_dir` is the direction of the ray (known).
- `C` is the center of the sphere (known).
- `r` is the radius of the sphere (known).

Let `oc = ray_origin - C` (oc is a vector).
	`||oc + t * ray_dir||^2 = r^2`

Expand the equation (`∣∣v∣∣^2 = v⋅v`):
	`(oc + t * ray_dir) . (oc + t * ray_dir) = r^2`, where:
- `.` is the dot product.

Using the dot product (`(a+b)⋅(a+b) = a⋅a + 2(a⋅b) + b⋅b)`:
	`(oc . oc) + 2t(oc . ray_dir) + t^2(ray_dir . ray_dir) = r^2`

Rearrange the into a quadratic equation (ax^2 + bx + c = 0):
	`(ray_dir . ray_dir)t^2 + 2(oc . ray_dir)t + (oc . oc) - r^2 = 0`, where:
- `a = ray_dir . ray_dir = ||ray_dir||^2`
- `b = 2(oc . ray_dir)`
- `c = (oc . oc) - r^2 = ||oc||^2 - r^2`

The quadratic formula is used to solve the equation:
	`t = (-b ± sqrt(b^2 - 4ac)) / 2a`
(for the derivation of the quadratic formula, see:
https://www.chilimath.com/lessons/intermediate-algebra/derive-quadratic-formula/
*/
double	calculate_discriminant(double a, double b, double c)
{
	double	discriminant;

	discriminant = (b * b) - (4.0 * a * c);
	return (discriminant);
}

/**
Calculates the smaller root of a quadratic equation
`x = (-b ± sqrt(b^2 - 4ac)) / 2a`. This smaller root corresponds to the first
intersection point of a ray with a sphere (point closer to the ray's origin).

 @param a 				The coefficient of the quadratic term.
 @param b 				The coefficient of the linear term.
 @param discriminant 	The discriminant of the quadratic equation (`b^2 - 4ac`).

 @return 				The smaller root (`t` value) of the quadratic equation.

 @details
In ray-sphere intersection calculations, the quadratic equation is derived from:
  `||ray_origin + t * ray_dir - C||^2 = r^2`, where:
- `ray_origin` is the starting point of the ray.
- `ray_dir` is the direction of the ray.
- `C` is the center of the sphere.
- `r` is the radius of the sphere.

The solutions `t` are the distances along the ray to the intersection points:
- The smaller root (`t1 = (-b - sqrt(D)) / (2a)`) is the first
  (closest) intersection.
- The larger root (`t2 = (-b + sqrt(D)) / (2a)`) is the second
  farther) intersection.
- (D is the discriminant `b^2 - 4ac`).

Solutions for `t` (t1, t2) can be interpreted as follows:
- If `t1 > 0`, it is the valid intersection point in front of the ray's origin.
- If `t1 = 0`, the ray is tangent to the sphere.
- If `t1 < 0` and `t2 > 0`, the ray originates inside the sphere, and `t2` is
  the valid exit point.
- If both roots are negative, there is no intersection (sphere not visible).
*/
double	calculate_smaller_root(double a, double b, double discriminant)
{
	double	t1;

	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	return (t1);
}

/**
Calculates the larger root of a quadratic equation
`x = (-b ± sqrt(b^2 - 4ac)) / 2a`. This larger root corresponds to the second
intersection point of a ray with a sphere (point closer to the ray's origin), OR
the exit point if the ray originates inside the sphere.

 @param a 				The coefficient of the quadratic term.
 @param b 				The coefficient of the linear term.
 @param discriminant 	The discriminant of the quadratic equation (`b^2 - 4ac`).

 @return 				The larger root (`t` value) of the quadratic equation.

 @details
 See `calculate_smaller_root()`.
*/
double	calculate_larger_root(double a, double b, double discriminant)
{
	double	t1;

	t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	return (t1);
}

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
		*t = calculate_smaller_root(1.0, b, discriminant);
		if (*t >= 0.0)
			return (1);
		*t = calculate_larger_root(1.0, b, discriminant);
		if (*t >= 0.0)
			return (1);
	}
	return (0);
}

/**
Function to find the intersection of a ray with a plane.

 @param ray_origin 	The starting point of the ray (3D vector).
 @param ray_dir 	The normalized direction vector of the ray..
 @param plane 		Pointer to the plane structure.
 @param t 			A pointer to store the distance to the intersection point
 					(if found).

 @return 			`1` if an intersection is found (and t is set to the
					intersection distance);
					`0` if there is no intersection within the FOV.

 @details
See details of the mathematically derived ray-plane intersection algorithm on
https://github.com/Busedame/miniRT/blob/main/README.md#ray-object-intersection

 @note
Due to floating-point precision limitations, directly comparing a dot product to zero
can be unreliable. A small threshold (1e-6) is used to determine if the ray is parallel
to the plane. Values below this threshold are considered too close to zero, indicating
parallelism or preventing division by very small numbers, which could lead to inaccuracies.
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
