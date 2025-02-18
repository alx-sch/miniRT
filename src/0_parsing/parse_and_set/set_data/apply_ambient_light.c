/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:13 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/18 21:54:48 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/* Updates an object's color based on the ambient light. */
static void	apply_ambient_light_to_object(t_obj *obj, t_rt *rt)
{
	float	intensity;
	float	ambi_r;
	float	ambi_g;
	float	ambi_b;

	intensity = rt->scene.ambi_light.ratio;
	ambi_r = (float)rt->scene.ambi_light.color.r * intensity;
	ambi_g = (float)rt->scene.ambi_light.color.g * intensity;
	ambi_b = (float)rt->scene.ambi_light.color.b * intensity;
	obj->color.r = (float)obj->color.r * ambi_r / 255.0;
	obj->color.g = (float)obj->color.g * ambi_g / 255.0;
	obj->color.b = (float)obj->color.b * ambi_b / 255.0;
}

/* Iterates through all objects and updates their color based
on ambient light. */
void	apply_ambient_light(t_rt **rt)
{
	t_list	*current_obj;
	t_obj	*obj;

	current_obj = (*rt)->scene.objs;
	while (current_obj != NULL)
	{
		obj = (t_obj *)current_obj->content;
		apply_ambient_light_to_object(obj, *rt);
		current_obj = current_obj->next;
	}
}
