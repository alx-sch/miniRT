/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_ray_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/18 08:03:35 by aschenk          ###   ########.fr       */
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
static t_vec3	compute_ray_direction(int x, int y, t_cam cam)
{
	double	norm_x;
	double	norm_y;
	t_vec3	ray_cam_dir;
	t_vec3	ray_world_dir;

	norm_x = ((2.0 * (x + 0.5) / WINDOW_W) - 1.0) * cam.aspect_ratio
		* cam.scale;
	norm_y = (1.0 - (2.0 * (y + 0.5) / WINDOW_H)) * cam.scale;
	ray_cam_dir = vec3_new(norm_x, norm_y, 1.0);
	ray_world_dir = vec3_add(\
						vec3_add(\
							vec3_mult(cam.right, ray_cam_dir.x), \
							vec3_mult(cam.up, ray_cam_dir.y)), \
						vec3_mult(cam.ori, ray_cam_dir.z));
	return (vec3_norm(ray_world_dir));
}

/**
Render a single pixel on the screen by computing the ray direction and finding
the closest intersection.

 @param rt 	Pointer to the main structure of the program.
 @param x 	The x-coordinate of the pixel.
 @param y 	The y-coordinate of the pixel.
*/
static void	render_pixel(t_rt *rt, int x, int y)
{
	t_vec3	ray_dir;
	t_ixr	cam_ray_ixr;

	ray_dir = compute_ray_direction(x, y, rt->scene.cam);
	find_ix(rt->scene.cam.pos, ray_dir, rt, &cam_ray_ixr);
	compute_color(ray_dir, rt, &cam_ray_ixr);
	set_pixel_color(&rt->mlx.img, x, y, cam_ray_ixr.ixn_color);
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
