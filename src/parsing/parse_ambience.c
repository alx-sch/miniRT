/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambience.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:45:34 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/19 15:50:55 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ambience_rgb(t_scene *scene, char **rgb)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (rgb[i])
	{
		if (!only_numbers_and_newline(rgb[i]))
			return (1);
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			return (1);
		if (i == 0)
			scene->amb.color_r = value;
		else if (i == 1)
			scene->amb.color_g = value;
		else if (i == 2)
			scene->amb.color_b = value;
		i++;
	}
	return (0);
}

int	parse_ambience(t_scene *scene)
{
	char	**rgb;

	if (array_length(scene->pars.elem_data) != 3)
		return (ERR_AMB_FIELDS);
	scene->amb.light = ft_atof(scene->pars.elem_data[1]);
	if (scene->amb.light < 0.0 || scene->amb.light > 1.0)
		return (ERR_AMB_LIGHT);
	rgb = ft_split(scene->pars.elem_data[2], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	if (array_length(rgb) != 3)
		scene->pars.error_code = ERR_AMB_COLOR_FIELDS;
	if (ambience_rgb(scene, rgb))
		scene->pars.error_code = ERR_AMB_COLOR_VALUES;
	ft_freearray(rgb);
	return (scene->pars.error_code);
}
