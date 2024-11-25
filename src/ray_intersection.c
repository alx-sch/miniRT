/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:30:04 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/25 16:44:22 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
- ||P-C||  is the distance between the point P and the center C.
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

 @param a 							The coefficient of the quadratic term.
 @param b 							The coefficient of the linear term.
 @param discriminant 		The discriminant of the quadratic equation (`b^2 - 4ac`).

 @return 								The smaller root (`t` value) of the quadratic equation.

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

**Considerations:**
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

 @param a 							The coefficient of the quadratic term.
 @param b 							The coefficient of the linear term.
 @param discriminant 		The discriminant of the quadratic equation (`b^2 - 4ac`).

 @return 								The larger root (`t` value) of the quadratic equation.

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
Function to find the intersection of a ray with a sphere

 @param ray_origin 	The starting point of the ray (3D vector).
 @param ray_dir 		The direction vector of the ray (assumed to be normalized).
 @param sphere 			Pointer to the sphere structure (contains center and radius).
 @param t 					Pointer to store the distance to the first intersection
										point (if found).

 @return 						`1` if an intersection is found (and t is set to the
										intersection distance);
										`0` if there is no intersection.

 @note 							`a = vec3_dot(ray_dir, ray_dir)` is 1.0 if the ray direction
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

// // Function to compute the ray direction with FOV consideration
t_vec3 compute_ray_direction(int x, int y, t_cam cam, int screen_width, int screen_height)
{
    double aspect_ratio = (double)screen_width / (double)screen_height;
    double scale = tan((cam.fov * 0.5) * M_PI / 180.0); // scale based on FOV

    // Normalized device coordinates (-1 to 1 range for both axes)
    double nx = (2.0 * (x + 0.5) / screen_width - 1.0) * aspect_ratio * scale;
    double ny = (1.0 - 2.0 * (y + 0.5) / screen_height) * scale;

    // Ray direction is in camera space
    t_vec3 ray_dir = {
        nx,
        ny,
        1.0 // Looking along the Z-axis (camera space)
    };

    // Normalize the direction to ensure it's a unit vector
    double length = sqrt(ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z);
    ray_dir.x /= length;
    ray_dir.y /= length;
    ray_dir.z /= length;

    return ray_dir;
}


void	render_scene(t_rt *rt, int bg_color)
{
    int x, y;
    t_vec3 ray_origin;
    t_vec3 ray_dir;
    double t, closest_t;
    int pixel_color;
    t_list *current_obj;
    t_obj_data *obj_data;

    // Loop through each pixel
    for (y = 0; y < WINDOW_H; y++)
    {
        for (x = 0; x < WINDOW_W; x++)
        {
            // Compute the direction of the ray for this pixel
            ray_origin.x = rt->scene.cam.position.x;
            ray_origin.y = rt->scene.cam.position.y;
            ray_origin.z = rt->scene.cam.position.z;

            ray_dir = compute_ray_direction(x, y, rt->scene.cam, WINDOW_W, WINDOW_H);

            // Initialize hit to false and pixel color to background color
            pixel_color = bg_color;
            closest_t = INFINITY;

            // Iterate over all objects in the scene
            current_obj = rt->scene.objs;
            while (current_obj != NULL)
            {
                obj_data = (t_obj_data *)current_obj->content;
                if (obj_data->sp.object_type == SPHERE)
                {
                    // Check for intersection with the sphere
                    if (ray_intersect_sphere(ray_origin, ray_dir, &obj_data->sp, &t))
                    {
                        // If a hit occurs and it's closer than the previous hit, update the pixel color
                        if (t < closest_t)
                        {
                            closest_t = t;
                            pixel_color = color_to_hex(obj_data->sp.color);
                        }
                    }
                }
                current_obj = current_obj->next;
            }

            // Set pixel color using the set_pixel_color function
            set_pixel_color(&rt->mlx.img, x, y, pixel_color);
        }
    }
}
