/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:08 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 17:06:03 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	light_coordinates(t_scene *scene)
{
	char	**coords;
	int		i;

	i = 0;
	coords = ft_split(scene->pars.elem_data[1], ',');
	if (!coords)
		return (4);
	if (array_length(coords) != 3)
		return (18);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (19);
	}
	scene->light_x = ft_atof(coords[0]);
	scene->light_y = ft_atof(coords[1]);
	scene->light_z = ft_atof(coords[2]);
	ft_freearray(coords);
	return (0);
}

static int	light_brightness(t_scene *scene)
{
	if (!only_numbers_dec_pt_and_newline(scene->pars.elem_data[2]))
		return (20);
	scene->light_bright = ft_atof(scene->pars.elem_data[2]);
	if (scene->light_bright < 0 || scene->light_bright > 1)
		return (20);
	return (0);
}

static int	light_color(t_scene *scene, char **rgb)
{
	int		value;

	value = 0;
	if (array_length(rgb) != 3)
		return (21);
	if (!only_numbers_and_newline(rgb[0]) || !only_numbers_and_newline(rgb[1])
		|| !only_numbers_and_newline(rgb[2]))
		return (22);
	value = ft_atoi(rgb[0]);
	if (value < 0 || value > 255)
		return (22);
	scene->light_color_r = value;
	value = ft_atoi(rgb[1]);
	if (value < 0 || value > 255)
		return (22);
	scene->light_color_g = value;
	value = ft_atoi(rgb[2]);
	if (value < 0 || value > 255)
		return (22);
	scene->light_color_b = value;
	return (0);
}

int	parse_light(t_scene *scene)
{
	int		arr_len;
	char	**rgb;

	rgb = NULL;
	arr_len = array_length(scene->pars.elem_data);
	if (arr_len != 3 && arr_len != 4)
		return (17);
	scene->pars.error_code = light_coordinates(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	scene->pars.error_code = light_brightness(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	if (arr_len == 4)
	{
		rgb = ft_split(scene->pars.elem_data[3], ',');
		if (!rgb)
			return (4);
		scene->pars.error_code = light_color(scene, rgb);
		ft_freearray(rgb);
		if (scene->pars.error_code != 0)
			return (scene->pars.error_code);
	}
	return (0);
}
