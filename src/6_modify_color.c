/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_modify_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:23:12 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/24 18:19:44 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_final_color(t_ambi_light *amb, double final, t_color rgb)
{
	final = adjust_to_color_range(final + amb->ratio, 0.0, 1.0);
	rgb.r = adjust_to_color_range(rgb.r * final, 0, 255);
	rgb.g = adjust_to_color_range(rgb.g * final, 0, 255);
	rgb.b = adjust_to_color_range(rgb.b * final, 0, 255);
	return (color_to_hex(rgb));
}

int	add_color_effects(t_rt *rt, t_ixr *ixr, t_color rgb)
{
	t_vec3		reflection_vec;
	t_vec3		view_vec;
	double		spec_intensity;
	double		intensity;
	double		final;

	spec_intensity = 0.0;
	intensity = vec3_dot(ixr->shadow.normal, ixr->shadow.light_dir);
	if (intensity < 0)
		intensity = 0.0;
	if (intensity != 0.0)
	{
		reflection_vec = vec3_norm(vec3_sub(vec3_scale(ixr->shadow.normal, 2 * \
			vec3_dot(ixr->shadow.normal, ixr->shadow.light_dir)), \
			ixr->shadow.light_dir));
		view_vec = vec3_norm(vec3_sub(rt->scene.cam.pos, \
		ixr->shadow.offset_origin));
		spec_intensity = pow(vec3_dot(reflection_vec, view_vec), 500);
	}
	if (spec_intensity < 0.0)
		spec_intensity = 0.0;
	final = (spec_intensity + intensity) * rt->scene.light.ratio;
	return (set_final_color(&rt->scene.ambi_light, final, rgb));
}

t_color	set_original_color(t_obj_data *obj)
{
	t_color	rgb;

	if (obj->cy.object_type == CYLINDER)
	{
		rgb.r = obj->cy.color.r;
		rgb.g = obj->cy.color.g;
		rgb.b = obj->cy.color.b;
		obj->cy.hit = 1;
	}
	else if (obj->sp.object_type == SPHERE)
	{
		rgb.r = obj->sp.color.r;
		rgb.g = obj->sp.color.g;
		rgb.b = obj->sp.color.b;
		obj->sp.hit = 1;
	}
	else if (obj->pl.object_type == PLANE)
	{
		rgb.r = obj->pl.color.r;
		rgb.g = obj->pl.color.g;
		rgb.b = obj->pl.color.b;
		obj->pl.hit = 1;
	}
	return (rgb);
}

/**
If an object has been hit, it means that this is the current hitpoint.
To avoid an object reading itself as blocking for the light source, the
hit object stores information on whether it's been hit or not.
This function resets the hit variable for the hit object to 0.
*/
static void	reset_hit_object(t_obj_data *obj)
{
	if (obj->cy.object_type == CYLINDER)
		obj->cy.hit = 0;
	else if (obj->sp.object_type == SPHERE)
		obj->sp.hit = 0;
	else if (obj->pl.object_type == PLANE)
		obj->pl.hit = 0;
}

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
void	modify_color(t_vec3 ray_dir, t_rt *rt, t_ixr *ixr)
{
	t_color	rgb;

	rgb = set_original_color(ixr->hit_obj);
	ixr->shadow = init_shadow(rt, ixr, ray_dir);
	if (is_ray_in_shadow(rt, ixr))
	{
		rgb.r *= rt->scene.ambi_light.ratio;
		rgb.g *= rt->scene.ambi_light.ratio;
		rgb.b *= rt->scene.ambi_light.ratio;
		ixr->ixn_color = color_to_hex(rgb);
	}
	else
		ixr->ixn_color = add_color_effects(rt, ixr, rgb);
	reset_hit_object(ixr->hit_obj);
}
