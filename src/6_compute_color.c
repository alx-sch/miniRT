/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_compute_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:23:12 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/18 09:06:33 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Mixes the spotlight and specular light with the ambient light ratio -
and then scales that with original color, making sure that it remains within
RGB range. Returns the final color of the pixel.*/
// int	set_final_color(t_ambi_light *amb, double final, t_color rgb)
// {
// 	if (final > 1.0)
// 		final = 1.0;
// 	rgb.r *= final;
// 	rgb.g *= final;
// 	rgb.b *= final;
// 	return (color_to_hex(rgb));
// }

// /**
// This function adds diffuse and specular light to the hitpoint, if the hitpoint
// is not in shadow.
// @param intensity Diffuse lighting. Computes the contribution of light hitting
// the surface based on the angle between the surface normal and light direction.
// @param reflection_vec The direction that light would travel if it reflects off
// the surface at the intersection point, following the laws of reflection. It
// helps calculate specular highlights, as these depend on how closely aligned the
// reflection vector is with the view vector (the closer, the brighter the
// highlight).
// @param view_vec The direction from the point on the object's surface
// (where the light hits) to the camera. It helps simulate how the camera "sees"
// the reflection of the light source on the object's surface.
// @param spec_intensity Calculates the reflection vector and the view vector.
// Specular highlight happens when the view vector aligns closely with the
// reflection vector. The spec_intensity is calculated using the dot product of
// these vectors, raised to a power (sharpness factor).
// @param final Stores the combination of diffuse and specular contributions,
// scaling by the light's intensity ratio.
// @param set_final_color Function that combines all elements together and returns
// the final color in hex-format.
// */
// int	add_color_effects(t_rt *rt, t_ixr *ixr, t_color rgb)
// {
// 	t_vec3		reflection_vec;
// 	t_vec3		view_vec;
// 	double		spec_intensity;
// 	double		intensity;
// 	double		final;

// 	spec_intensity = 0.0;
// 	intensity = vec3_dot(ixr->shadow.normal, ixr->shadow.light_dir);
// 	if (intensity < 0)
// 		intensity = 0.0;
// 	if (intensity != 0.0)
// 	{
// 		reflection_vec = vec3_norm(vec3_sub(vec3_scale(ixr->shadow.normal, 2 * \
// 			vec3_dot(ixr->shadow.normal, ixr->shadow.light_dir)), \
// 			ixr->shadow.light_dir));
// 		view_vec = vec3_norm(vec3_sub(rt->scene.cam.pos, \
// 		ixr->shadow.offset_origin));
// 		spec_intensity = pow(vec3_dot(reflection_vec, view_vec), 50);
// 	}
// 	if (spec_intensity < 0.0)
// 		spec_intensity = 0.0;
// 	final = (spec_intensity + intensity) * rt->scene.light.ratio
// 		+ rt->scene.ambi_light.ratio;
// 	return (set_final_color(&rt->scene.ambi_light, final, rgb));
// }

/*Returns the rgb values of the color of the hit object (the object that was hit
from camera ray).*/
// t_color	set_original_color(t_obj *obj)
// {
// 	t_color	rgb;

// 	rgb.r = obj->cy.color.r;
// 	rgb.g = obj->cy.color.g;
// 	rgb.b = obj->cy.color.b;
// 	obj->cy.hit = 1;
// 	}
// 	else if (obj->sp.object_type == SPHERE)
// 	{
// 		rgb.r = obj->sp.color.r;
// 		rgb.g = obj->sp.color.g;
// 		rgb.b = obj->sp.color.b;
// 		obj->sp.hit = 1;
// 	}
// 	else if (obj->pl.object_type == PLANE)
// 	{
// 		rgb.r = obj->pl.color.r;
// 		rgb.g = obj->pl.color.g;
// 		rgb.b = obj->pl.color.b;
// 		obj->pl.hit = 1;
// 	}
// 	return (rgb);
// }

// /**
// If an object has been hit, it means that this is the current hitpoint.
// To avoid an object reading itself as blocking for the light source, the
// hit object stores information on whether it's been hit or not.
// This function resets the hit variable for the hit object to 0.
// */
// static void	reset_hit_object(t_obj *obj)
// {
// 	if (obj->cy.object_type == CYLINDER)
// 		obj->cy.hit = 0;
// 	else if (obj->sp.object_type == SPHERE)
// 		obj->sp.hit = 0;
// 	else if (obj->pl.object_type == PLANE)
// 		obj->pl.hit = 0;
// }

/**
@param rgb Gets set to the color of the hit object (already mixed with the
color of ambient light).
@param ixr->shadow Stores a shadow ray (a ray from hit object to the light
source).

The is_ray_in_shadow-function checks whether the hitpoint is in shadow or not.

If the hitpoint is in shadow, leave it as it is.

If the hitpoint is not in shadow, also calculate spotlight (at what angle does
the light hit and how far away) and specular light (shiny effects).

Sets the ixn_color variable to the final color.
*/
void	compute_color(t_vec3 ray_dir, t_rt *rt, t_ixr *ixr)
{
	t_color	rgb;
	t_ixr	shadow_ray_ix;
	t_vec3  shadow_dir;
	double  shadow_len;

	ixr->ixn_color = BG_COLOR;
	if (!ixr->hit_obj)
		return ;
	shadow_dir = vec3_norm(vec3_sub(rt->scene.light.position, ixr->hit_point));
	shadow_len = vec3_length(vec3_sub(rt->scene.light.position, ixr->hit_point));
	find_ix(ixr->hit_point, shadow_dir, rt, &shadow_ray_ix);
	if (shadow_ray_ix.hit_obj && shadow_ray_ix.t_hit < shadow_len)
	{
		ixr->ixn_color = 0;
		return ;
	}
	ixr->ixn_color = color_to_hex(ixr->hit_obj->color);

	//ixr->shadow = init_shadow(rt, ixr, ray_dir);
	// if (is_ray_in_shadow(rt, ixr))
	// {
	// 	rgb.r *= rt->scene.ambi_light.ratio;
	// 	rgb.g *= rt->scene.ambi_light.ratio;
	// 	rgb.b *= rt->scene.ambi_light.ratio;
	// 	ixr->ixn_color = color_to_hex(rgb);
	// }
	// else
	// 	ixr->ixn_color = add_color_effects(rt, ixr, rgb);
	// reset_hit_object(ixr->hit_obj);
}
