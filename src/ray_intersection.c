/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:30:04 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/25 18:49:50 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

                // Check for intersection with sphere
                if (obj_data->sp.object_type == SPHERE)
                {
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

                // Check for intersection with plane
                if (obj_data->pl.object_type == PLANE)
                {
                    if (ray_intersect_plane(ray_origin, ray_dir, &obj_data->pl, &t))
                    {
                        // If a hit occurs and it's closer than the previous hit, update the pixel color
                        if (t < closest_t)
                        {
                            closest_t = t;
                            pixel_color = color_to_hex(obj_data->pl.color);
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
