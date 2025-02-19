/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_parse_and_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:45:34 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/18 22:18:32 by aschenk          ###   ########.fr       */
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
	scene->ambi_light.ratio = ft_atod(scene->pars.elem_data[1]);
	if (scene->ambi_light.ratio < 0.0 || scene->ambi_light.ratio > 1.0)
		return (ERR_AMB_LIGHT);
	rgb = ft_split(scene->pars.elem_data[2], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	if (check_color(rgb, &scene->pars.error_code, ERR_AMB_COLOR_FIELDS) != 0)
	{
		ft_freearray(rgb);
		return (scene->pars.error_code);
	}
	set_color(rgb, &scene->ambi_light.color.r, &scene->ambi_light.color.g, \
	&scene->ambi_light.color.b);
	return (scene->pars.error_code);
}
