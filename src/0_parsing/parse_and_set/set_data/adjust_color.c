/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:13 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/22 19:53:19 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*If the object's new color is smaller than 0 or greater than 255 (outside
of the RGB range), updates the color to 0 or 255.*/
double	adjust_to_color_range(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/*Mixes the object color with the ambient light and intensity, and returns
the result.*/
t_color	mix_ambient_light(t_color object_color, t_color ambient_color)
{
	t_color	result;

	result.r = adjust_to_color_range(object_color.r * \
	ambient_color.r / 255, 0, 255);
	result.g = adjust_to_color_range(object_color.g * \
	ambient_color.g / 255, 0, 255);
	result.b = adjust_to_color_range(object_color.b * \
	ambient_color.b / 255, 0, 255);
	return (result);
}

/*Updates an object's color and hex color.*/
static void	update_object_color(t_color *color, int *hex_color, t_rt *rt)
{
	*color = mix_ambient_light(*color, rt->scene.ambi_light.color);
	*hex_color = color_to_hex(*color);
}

/*Iterates through all the objects, and updating their color values based
on the ambient light color and intensity.*/
void	adjust_color(t_rt **rt)
{
	t_list		*current_obj;
	t_obj_data	*obj_data;

	current_obj = (*rt)->scene.objs;
	while (current_obj != NULL)
	{
		obj_data = (t_obj_data *)current_obj->content;
		if (obj_data->pl.object_type == PLANE)
			update_object_color(&obj_data->pl.color, &obj_data->pl.hex_color, \
			*rt);
		else if (obj_data->sp.object_type == SPHERE)
			update_object_color(&obj_data->sp.color, &obj_data->sp.hex_color, \
			*rt);
		else if (obj_data->cy.object_type == CYLINDER)
			update_object_color(&obj_data->cy.color, &obj_data->cy.hex_color, \
			*rt);
		current_obj = current_obj->next;
	}
}
