/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_set_ambience.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:45:34 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 17:07:42 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Parses and sets an ambience object.
1. Checks if there's a correct amount of fields (3).
2. Checks if the light brightness is valid (between 0 and 1).
3. Checks if the color values are valid.
Sets all values and returns 0 upon success, and an error code upon error.*/
int	parse_and_set_ambience(t_scene *scene)
{
	char	**rgb;

	if (!correct_amt_of_fields(scene->pars.elem_data, 3))
		return (ERR_AMB_FIELDS);
	scene->amb.light = ft_atod(scene->pars.elem_data[1]);
	if (scene->amb.light < 0.0 || scene->amb.light > 1.0)
		return (ERR_AMB_LIGHT);
	rgb = ft_split(scene->pars.elem_data[2], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	if (check_color(rgb, &scene->pars.error_code, ERR_AMB_COLOR_FIELDS) != 0)
	{
		ft_freearray(rgb);
		return (scene->pars.error_code);
	}
	set_color(rgb, &scene->amb.color_r, &scene->amb.color_g, \
	&scene->amb.color_b);
	ft_freearray(rgb);
	return (scene->pars.error_code);
}
