/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_ray_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/18 21:57:06 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Handles the computation of ray directions for rendering pixels and performs
the rendering of the entire scene by calculating intersections for rays cast
through the camera's view.
*/

#include "main.h"

// IN FILE:

void	render_scene(t_rt *rt);

/**
Render a single pixel on the screen by computing the ray direction and finding
the closest intersection.

 @param rt 	Pointer to the main structure of the program.
 @param x 	The x-coordinate of the pixel.
 @param y 	The y-coordinate of the pixel.
*/
static void	render_pixel(t_rt *rt, int x, int y)
{
	t_vec3	camera_ray_dir;
	t_ix	camera_ray_ix;
	t_shdw	shadow_ray;
	t_ix	shadow_ray_ix;

	camera_ray_dir = compute_camera_ray(x, y, rt->scene.cam);
	find_ix(rt->scene.cam.pos, camera_ray_dir, rt, &camera_ray_ix);
	if (!camera_ray_ix.hit_obj)
	{
		set_pixel_color(&rt->mlx.img, x, y, BG_COLOR);
		return ;
	}
	shadow_ray = compute_shadow_ray(&camera_ray_ix, rt->scene.light);
	find_ix(shadow_ray.ori, shadow_ray.dir, rt, &shadow_ray_ix);
	if (shadow_ray_ix.hit_obj && shadow_ray_ix.t_hit < shadow_ray.len)
		set_pixel_color(&rt->mlx.img, x, y, 0x000000); // actually it's obj_color in ambient light
	else
		set_pixel_color(&rt->mlx.img, x, y,
			color_to_hex(camera_ray_ix.hit_obj->color));

	// compute_color(camera_ray_dir, rt, &camera_ray_ix);
	// set_pixel_color(&rt->mlx.img, x, y, camera_ray_ix.ixn_color);
}

/**
Render the entire scene by iterating over each pixel and rendering it.

 @param rt 	Pointer to the main structure of the program.
*/
void	render_scene(t_rt *rt)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_H)
	{
		x = 0;
		while (x < WINDOW_W)
		{
			render_pixel(rt, x, y);
			x++;
		}
		y++;
	}
}
