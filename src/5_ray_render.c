/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_ray_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:47:07 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/20 23:20:45 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD.
*/

#include "main.h"

// IN FILE:

void	render_scene(t_rt *rt);

/**
Traces the camera ray and finds the intersection.
 @param rt 				Pointer to the main structure.
 @param camera_ray_ix 	Pointer to the intersection structure to be filled.
 @param x 				The x-coordinate of the pixel.
 @param y 				The y-coordinate of the pixel.

 @return				`1` if an intersection was found, `0` otherwise.
*/
static int	trace_camera_ray(t_rt *rt, t_ix *camera_ray_ix, int x, int y)
{
	t_vec3	camera_ray_dir;

	camera_ray_dir = compute_camera_ray(x, y, rt->scene.cam);
	find_ix(rt->scene.cam.pos, camera_ray_dir, rt, camera_ray_ix);
	return (camera_ray_ix->hit_obj != NULL);
}

/**
Handles the shadow ray calculation and checks for light obstruction
 @param rt 				Pointer to the main structure.
 @param camera_ray_ix 	Pointer to the intersection structure of the camera ray.

 @return				`1` if the shadow ray is obstructed, `0` otherwise.
*/
static int	handle_shadow_ray(t_rt *rt, t_ix *camera_ray_ix)
{
	t_shdw	shadow_ray;
	t_ix	shadow_ray_ix;

	shadow_ray = compute_shadow_ray(camera_ray_ix, rt->scene.light);
	find_ix(shadow_ray.ori, shadow_ray.dir, rt, &shadow_ray_ix);
	return (shadow_ray_ix.hit_obj && shadow_ray_ix.t_hit < shadow_ray.len);
}


//////
// SHADING
//////

/**
Calculate the reflection of a vector off a surface.
 @param v_in			The incoming vector.
 @param surface_normal	The normal of the surface.

 @return The reflected vector.
*/
t_vec3	reflect(t_vec3 v_in, t_vec3 surface_normal)
{
	t_vec3	v_out;

	v_out = vec3_sub(\
		v_in, \
		vec3_scale(surface_normal, \
			2.0 * vec3_dot(v_in, surface_normal)));
	return (v_out);
}

/**
Calculates the diffuse lighting for a given intersection point.
 @param rt 		Pointer to the main structure.
 @param ix 		Pointer to the intersection data.

 @return		The diffuse lighting value [0.0, 1.0].
*/
double	calculate_diffuse(t_rt *rt, t_ix *ix)
{
	double	diffuse;
	double	dot;

	dot = vec3_dot(ix->normal, ix->light_dir);
	if (dot < 0)
		dot = 0;
	diffuse = rt->scene.light.ratio * dot * K_DIFFUSE;
	return (diffuse);
}

/**
Makes sure that the color values don't overflow and are within the valid
range [0, 255].
 @param value The value to clamp.

 @return The clamped value.
*/
static double	clamp(double value, double max)
{
	if (value > max)
		return (max);
	return (value);
}
//////
// SHADING
//////


/**
Computes and applies the final color for a pixel based on shadows, diffuse and
specular lighting.
 - Determines if the point is in shadow.
 - If not, will incorporate diffuse and specular lighting.
 - Sets the computed color to the pixel.
 @param rt 				Pointer to the main structure.
 @param camera_ray_ix 	Pointer to the intersection structure to be filled.
 @param x 				The x-coordinate of the pixel.
 @param y 				The y-coordinate of the pixel.
*/
static void	shade_pixel(t_rt *rt, t_ix *camera_ray_ix, int x, int y)
{
	t_color	original_color;
	t_color	ambient_color;
	t_color	diffuse_color;
	//t_color	specular_color;
	double	attenuation;
	t_color	final_color;
	int		is_shadowed;
	double	diffuse;

	int r = 0;
	int g = 0;
	int b = 0;

	original_color = camera_ray_ix->hit_obj->color;
	ambient_color = camera_ray_ix->hit_obj->color_in_amb;
	is_shadowed = handle_shadow_ray(rt, camera_ray_ix);
	if (is_shadowed)
	{
		final_color = ambient_color;
	}
	else
	{
		attenuation = K_DISTANCE * 100 / (camera_ray_ix->light_dist * camera_ray_ix->light_dist);
		attenuation = clamp(attenuation, 1.0);
		//attenuation = 1.0;
		diffuse = calculate_diffuse(rt, camera_ray_ix);
		diffuse_color.r = original_color.r * diffuse * attenuation;
		diffuse_color.g = original_color.g * diffuse * attenuation;
		diffuse_color.b = original_color.b * diffuse * attenuation;
		r = clamp(ambient_color.r + diffuse_color.r, 255);
		g = clamp(ambient_color.g + diffuse_color.g, 255);
		b = clamp(ambient_color.b + diffuse_color.b, 255);
		final_color.r = r;
		final_color.g = g;
		final_color.b = b;
	}
	set_pixel_color(&rt->mlx.img, x, y, color_to_hex(final_color));
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
	t_ix	camera_ray_ix;

	if (trace_camera_ray(rt, &camera_ray_ix, x, y) == 0)
	{
		set_pixel_color(&rt->mlx.img, x, y, BG_COLOR);
		return ;
	}
	shade_pixel(rt, &camera_ray_ix, x, y);
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
