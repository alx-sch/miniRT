/*
Functions for rendering a 3D scene by tracing rays from the camera and
calculating intersections with objects in the scene.
The rendering process includes the following steps:
 1.	Trace the camera ray to find the closest intersection with an object.
 2. Check for shadows by calculating a shadow ray to determine if the light
 	is blocked.
 3. Apply diffuse and specular lighting if the point is not in shadow,
 	otherwise use ambient color.
 4. Set the color of the pixel based on the computed shading.
 5. Repeat for every pixel to render the entire scene.
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
static void	shade_pixel(t_rt *rt, t_ix *ix, int x, int y)
{
	int		is_shadowed;
	t_shade	pix;

	is_shadowed = handle_shadow_ray(rt, ix);
	if (is_shadowed)
		pix.shaded = ix->hit_obj->color_in_amb;
	else
		pix = get_shading(rt, ix);
	set_pixel_color(&rt->mlx.img, x, y, color_to_hex(pix.shaded));
}

/**
Renders a single pixel on the screen by computing the ray direction and finding
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
Renders the entire scene by iterating over each pixel and rendering it.
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
