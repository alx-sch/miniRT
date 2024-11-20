/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:35:34 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/20 23:22:32 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Function to subtract two vectors.
 @param v1 	The first vector.
 @param v2 	The second vector.

 @return 	The result of the subtraction of the two vectors (v1 - v2).
*/
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

/**
Function to dot two vectors.
 @param v1 	The first vector.
 @param v2 	The second vector.

 @return 	The dot product of the two vectors.
*/
double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	double	result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (result);
}

/**
Function to multiply a vector by a scalar.
 @param v		The vector to scale.
 @param scalar 	The scalar value to multiply the vector by.

 @return 		The scaled vector.
*/
t_vec3	vec3_scale(t_vec3 v, double scalar)
{
	t_vec3	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

// Function to find the intersection of a ray with a sphere
int	ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir, t_sphere *sphere,
	double *t)
{
	t_vec3 oc = vec3_sub(ray_origin, sphere->center);
	double a = vec3_dot(ray_dir, ray_dir);
	double b = 2.0 * vec3_dot(oc, ray_dir);
	double c = vec3_dot(oc, oc) - (sphere->radius * sphere->radius);
	double discriminant = b * b - 4.0 * a * c;

    if (discriminant > 0) // There are intersections
    {
        *t = (-b - sqrt(discriminant)) / (2.0 * a);
        if (*t > 0)
            return 1; // Valid intersection
    }
    return 0; // No intersection
}

// Function to compute the ray direction with FOV consideration
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
