/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambience.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:45:34 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 15:22:37 by nholbroo         ###   ########.fr       */
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
			scene->amb_color_r = value;
		else if (i == 1)
			scene->amb_color_g = value;
		else if (i == 2)
			scene->amb_color_b = value;
		i++;
	}
	return (0);
}

int	parse_ambience(t_scene *scene)
{
	char	**rgb;

	if (array_length(scene->pars.elem_data) != 3)
		return (7);
	scene->amb_light = ft_atof(scene->pars.elem_data[1]);
	if (scene->amb_light < 0.0 || scene->amb_light > 1.0)
		return (8);
	rgb = ft_split(scene->pars.elem_data[2], ',');
	if (!rgb)
		return (4);
	if (array_length(rgb) != 3)
		scene->pars.error_code = 9;
	if (ambience_rgb(scene, rgb))
		scene->pars.error_code = 10;
	ft_freearray(rgb);
	return (scene->pars.error_code);
}
