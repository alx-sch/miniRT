/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_pixel_shading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:10:11 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/21 01:51:00 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "main.h"

// IN_FILE:

t_shade	get_shading(t_rt *rt, t_ix *ix);

/**
Calculates the diffuse lighting coefficient for a given intersection point.
 @param rt 		Pointer to the main structure.
 @param ix 		Pointer to the intersection data.

 @return		The diffuse lighting coefficient value [0.0, 1.0].
*/
static double	get_diffuse_coefficient(t_rt *rt, t_ix *ix)
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
Computes the shading for a pixel based on the object's color and light
properties.
 @param rt	Pointer to the main struct containing light properties.
 @param ix	Pointer to the ray/pixel intersection data.

 @return	A `t_pix_shade` struct with the computed shading components.
*/
t_shade	get_shading(t_rt *rt, t_ix *ix)
{
	t_shade	pix;

	pix.base = ix->hit_obj->color;
	pix.light = rt->scene.light.color;
	pix.ambient = ix->hit_obj->color_in_amb;
	pix.diff_coeff = get_diffuse_coefficient(rt, ix);
	pix.fade = K_FADE * 100 / (ix->light_dist * ix->light_dist);
	pix.fade = clamp(pix.fade, 1.0);
	pix.diffuse.r = pix.base.r * pix.light.r / 255 * pix.diff_coeff * pix.fade;
	pix.diffuse.g = pix.base.g * pix.light.g / 255 * pix.diff_coeff * pix.fade;
	pix.diffuse.b = pix.base.b * pix.light.b / 255 * pix.diff_coeff * pix.fade;
	// specular
	pix.shaded.r = clamp(pix.ambient.r + pix.diffuse.r, 255);
	pix.shaded.g = clamp(pix.ambient.g + pix.diffuse.g, 255);
	pix.shaded.b = clamp(pix.ambient.b + pix.diffuse.b, 255);
	return (pix);
}
