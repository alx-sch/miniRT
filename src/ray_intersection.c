/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:30:04 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/22 20:25:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Calculates the discriminant of a quadratic equation `ax^2 + bx + c = 0`, which
solves into x = (-b ± sqrt(b^2 - 4ac)) / 2a.

The discriminant D = `b^2 - 4ac` tells us:
- if D > 0, there are two real roots (the ray intersects the sphere at two
  points).
- if D = 0, there is one real root (the ray is tangent to the sphere, touching
  it at one point).
- if D < 0, there are no real roots (the ray does not intersect the sphere).

 @details
 Ray equation:
`P(t) = ray_origin + t * ray_dir`, where:
 - 	`P(t)` is the position of a point on the ray at a distance `t` from
 	the origin (3d vector).
-	`ray_origin` is the origin of the ray (3d vector).
-	`t` is the scaling factor for the direction vector; it's the distance
 	from origin to the point on the ray if the direction vector is normalized.
-	`ray_dir` is the direction of the ray (3d vector).

Sphere equation:
`||P-C||^2 = r^2`, where:
 - `P` is a point on the sphere (3d vector).
 - `C` is the center of the sphere (3d vector).
 - ||P-C||  is the distance between the point P and the center C.
 - `r` is the radius of the sphere.

Substitute the ray equation into the sphere equation:
`||ray_origin + t * ray_dir - C||^2 = r^2`, where:
 - `t` is the unknown variable.
 - `ray_origin` and `ray_dir` are known.
 - `C` is the center of the sphere (known).
 - `r` is the radius of the sphere (known).

 Let `oc = ray_origin - C` (oc is a vector).
 `||oc + t * ray_dir||^2 = r^2`

 Expand the equation:
 `(oc + t * ray_dir) . (oc + t * ray_dir) = r^2`, where:
 - `.` denotes the dot product.

 Using the dot product:
 `(oc . oc) + 2t(oc . ray_dir) + t^2(ray_dir . ray_dir) = r^2`

 Simplify the equation:
- `oc . oc = ||oc||^2`, squared distance from the origin to the sphere's center.
-> `||oc||^2 + 2t(oc . ray_dir) + t^2(ray_dir . ray_dir) = r^2`

Rearrange the into a quadratic equation (ax^2 + bx + c = 0):
`(ray_dir . ray_dir)t^2 + 2(oc . ray_dir)t + ||oc||^2 - r^2 = 0`, where:
 - `a = ray_dir . ray_dir = ||ray_dir||^2`
 - `b = 2(oc . ray_dir)`
 - `c = ||oc||^2 - r^2`

The quadratic formula is used to solve the equation:
t = (-b ± sqrt(b^2 - 4ac)) / 2a

 @param a 	The coefficient of the quadratic term.
 @param b 	The coefficient of the linear term.
 @param c 	The constant term.

 @return 	The discriminant of the quadratic equation.
*/
double	calculate_discriminant(double a, double b, double c)
{
	double	discriminant;

	discriminant = (b * b) - (4.0 * a * c);
	return (discriminant);
}

// Function to solve the quadratic equation for the smaller root
// Parameters: a, b, discriminant - quadratic coefficients and discriminant value
// Returns: The smaller root (t value) of the quadratic equation
double calculate_smaller_root(double a, double b, double discriminant) {
    return (-b - sqrt(discriminant)) / (2.0 * a);
}

// Function to find the intersection of a ray with a sphere
int	ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir, t_sphere *sphere, double *t)
{
	t_vec3 oc = vec3_sub(ray_origin, sphere->center);
	double a = vec3_dot(ray_dir, ray_dir);
	double b = 2.0 * vec3_dot(oc, ray_dir);
	double c = vec3_dot(oc, oc) - (sphere->radius * sphere->radius);
	double discriminant = calculate_discriminant(a, b, c);

	if (discriminant > 0)
	{
		*t = calculate_smaller_root(a, b, discriminant);;
		if (*t > 0)
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
