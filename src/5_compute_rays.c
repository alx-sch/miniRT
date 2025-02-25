/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_compute_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:26:27 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/25 20:43:20 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Functions to compute the camera and shadow rays for a given pixel.
*/

#include "main.h"

// IN FILE:

t_vec3	compute_camera_ray(int x, int y, t_cam cam);
t_shdw	compute_shadow_ray(t_ix *camera_ray_ix, t_light light);

/**
Computes the camera ray direction for a given pixel,
considering the camera's field of view (FOV), aspect ratio, and orientation.

1.	Convert Pixel Coordinates to Normalized Device Coordinates (NDC)
 -	`norm_x` and `norm_y` convert the pixel coordinates into a normalized range
 	from [−1 ,1] (centered around 0).
 -	`norm_x` is adjusted based on the aspect ratio to maintain the correct
  	proportions.
 - 	`norm_y` is flipped because the screen coordinate system typically has
 	(0,0) at the top left.

2.	Compute Ray Direction in Camera Space
 -	The ray direction in camera space is assumed to be in front of the camera:
	`ray_cam_dir  = vec3_new(norm_x, norm_y, 1.0)` (1.0 as to point forward).

3.	Transform the Ray to World Space
 - `ray_world_dir = cam.right * norm_x + cam.up * norm_y + cam.dir`
 -	The x component moves the ray in the right direction.
 -	The y component moves the ray in the up direction.
 -	The z component moves the ray in the forward direction.

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
t_vec3	compute_camera_ray(int x, int y, t_cam cam)
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
						vec3_mult(cam.dir, ray_cam_dir.z));
	return (vec3_norm(ray_world_dir));
}

/**
Utility function for `compute_normal()`.
Computes the normal vector for a point on the mantle of a cylinder.
 @param ix	Intersection data containing the hit point and cylinder object.

 @return	Normalized normal vector at the given hit point on the cyl's mantle.
*/
static t_vec3	compute_cyl_mantle_normal(t_ix *ix)
{
	t_vec3	axis_dir;
	t_vec3	axis_to_point;
	double	t;
	t_vec3	proj_point;

	axis_dir = ix->hit_obj->x.cy.orientation;
	axis_to_point = vec3_sub(ix->hit_point, ix->hit_obj->x.cy.center);
	t = vec3_dot(axis_to_point, axis_dir);
	proj_point = vec3_add(ix->hit_obj->x.cy.center, vec3_mult(axis_dir, t));
	return (vec3_norm(vec3_sub(ix->hit_point, proj_point)));
}

/**
Computes the surface normal at an intersection point.
 @param ix	Intersection data containing hit object information.

 @return 	Normalized normal vector at the intersection point.
*/
static t_vec3	compute_normal(t_ix *ix)
{
	t_vec3	normal;

	normal = vec3_new(0, 0, 0);
	if (ix->hit_obj->object_type == PLANE)
		normal = ix->hit_obj->x.pl.normal;
	else if (ix->hit_obj->object_type == SPHERE)
		normal = vec3_norm(vec3_sub(ix->hit_point, ix->hit_obj->x.sp.center));
	else if (ix->hit_obj->object_type == CYLINDER)
	{
		if (ix->cap_hit == TOP_CAP)
			normal = ix->hit_obj->x.cy.cap_top_normal;
		else if (ix->cap_hit == BOTTOM_CAP)
			normal = ix->hit_obj->x.cy.cap_bottom_normal;
		else
			normal = compute_cyl_mantle_normal(ix);
	}
	return (normal);
}

/**
Computes the shadow ray for a given intersection point and light source.
Also updates the provided intersection data with the light direction and
distance as well as the surface normal.
 @param camera_ray_ix	Pointer to the intersection data of the camera ray.
 @param light			Light source data.

 @return				Shadow ray structure containing an offset origin,
 						direction, and length.

 @details
An offset is applied to the shadow ray origin along the surface normal
to prevent shadow acne, which results from floating-point precision errors
causing self-intersections. This ensures the shadow ray starts slightly
above the surface, avoiding unintended intersections with its origin.
If the camera is wihtin the object, the offset is negated to ensure
the shadow ray starts inside the object, too.
*/
t_shdw	compute_shadow_ray(t_ix *camera_ray_ix, t_light light)
{
	t_vec3	hit_point;
	t_shdw	shadow_ray;
	t_vec3	offset;
	t_vec3	normal;

	hit_point = camera_ray_ix->hit_point;
	shadow_ray.dir = vec3_norm(vec3_sub(light.position, hit_point));
	camera_ray_ix->light_dir = shadow_ray.dir;
	shadow_ray.len = vec3_length(vec3_sub(light.position, hit_point));
	camera_ray_ix->light_dist = shadow_ray.len;
	normal = compute_normal(camera_ray_ix);
	if (camera_ray_ix->hit_obj->cam_in_obj)
		normal = vec3_mult(normal, -1.0);
	camera_ray_ix->normal = normal;
	offset = vec3_mult(normal, EPSILON);
	shadow_ray.ori = vec3_add(hit_point, offset);
	return (shadow_ray);
}
