/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/09 00:19:10 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
XXX
*/

#include "main.h"

/**
Function to compute the ray direction for a given pixel in a camera's view,
considering the camera's field of view (FOV), aspect ratio, and orientation.

 @param x		The horizontal pixel coordinate on the screen.
 @param y		The vertical pixel coordinate on the screen.
 @param cam		The camera object containing the FOV, orientation vector,
				and position.

 @return		The normalized direction vector of the ray passing through
				the pixel, in world space.

 @details
This function calculates the ray direction for a pixel by mapping the pixel
coordinates to normalized device coordinates (NDC), adjusting for the camera's
horizontal FOV and aspect ratio, and transforming the resulting direction into
world space using the camera's orientation.

See the README for more details on the derivation of this function:
https://github.com/Busedame/miniRT/blob/main/README.md#ray-direction-calculation
*/
t_vec3	compute_ray_direction(int x, int y, t_cam cam)
{
	double	norm_x;
	double	norm_y;
	t_vec3	ray_cam_dir;
	t_vec3	ray_world_dir;

	norm_x = ((2.0 * (x + 0.5) / WINDOW_W) - 1.0) * cam.aspect_ratio
		* cam.scale;
	norm_y = (1.0 - (2.0 * (y + 0.5) / WINDOW_H)) * cam.scale;
	ray_cam_dir = vec3_new(norm_x, norm_y, 1.0);
	ray_world_dir = vec3_add(
			vec3_add(vec3_mult(cam.right, ray_cam_dir.x),
				vec3_mult(cam.up, ray_cam_dir.y)),
			vec3_mult(cam.orientation, ray_cam_dir.z));
	return (vec3_norm(ray_world_dir));
}

void render_scene(t_rt *rt, int bg_color)
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

            ray_dir = compute_ray_direction(x, y, rt->scene.cam);

            // Initialize hit to false and pixel color to background color
            pixel_color = bg_color;
            closest_t = INFINITY;

            // Iterate over all objects in the scene
            current_obj = rt->scene.objs;
            while (current_obj != NULL)
            {
                obj_data = (t_obj_data *)current_obj->content;

                // Check for intersection with plane
                if (obj_data->pl.object_type == PLANE)
                {
                    if (ray_intersect_plane(ray_dir, &obj_data->pl, &t))
                    {
                        // If a hit occurs and it's closer than the previous hit, update the pixel color
                        if (t < closest_t)
                        {
                            closest_t = t;
                            pixel_color = color_to_hex(obj_data->pl.color);
                        }
                    }
                }

                // Check for intersection with sphere
                if (obj_data->sp.object_type == SPHERE)
                {
                    if (ray_intersect_sphere(ray_dir, &obj_data->sp, &t))
                    {
                        // If a hit occurs and it's closer than the previous hit, update the pixel color
                        if (t < closest_t)
                        {
                            closest_t = t;
                            pixel_color = color_to_hex(obj_data->sp.color);
                        }
                    }
                }

                // Check for intersection with sphere
                if (obj_data->cy.object_type == CYLINDER)
                {
                    if (ray_intersect_cylinder(ray_origin, ray_dir, &obj_data->cy, &t))
                    {
                        // If a hit occurs and it's closer than the previous hit, update the pixel color
                        //printf("Cylinder hit\n");
                        if (t < closest_t)
                        {
                            closest_t = t;
                            pixel_color = color_to_hex(obj_data->cy.color);
                        }
                    }
                    if (ray_intersect_cap_top(ray_origin, ray_dir, &obj_data->cy, &t))
                    {
                        // If a hit occurs and it's closer than the previous hit, update the pixel color
                      //  printf("Top cap hit\n");
                        if (t < closest_t)
                        {
                            closest_t = t;
                            pixel_color = color_to_hex(obj_data->cy.color);
                        }
                    }
                    if (ray_intersect_cap_bottom(ray_origin, ray_dir, &obj_data->cy, &t))
                    {
                        // If a hit occurs and it's closer than the previous hit, update the pixel color
                       // printf("Bottom cap hit\n");
                        if (t < closest_t)
                        {
                            closest_t = t;
                            pixel_color = color_to_hex(obj_data->cy.color);
                        }
                    }
                }

                // Move to the next object in the scene
                current_obj = current_obj->next;
            }

            // Set pixel color using the set_pixel_color function
            set_pixel_color(&rt->mlx.img, x, y, pixel_color);
        }
    }
}
