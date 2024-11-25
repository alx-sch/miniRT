/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_set_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:08 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:17:47 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	light_brightness(t_scene *scene, int *parsing_error)
{
	char	*sub;

	if (!only_numbers_dec_pt_and_newline(scene->pars.elem_data[2]))
		return (set_error_and_return(NULL, parsing_error, \
		ERR_LIGHT_BRIGHTNESS));
	if (ft_strchr(scene->pars.elem_data[2], '\n'))
	{
		sub = ft_substr(scene->pars.elem_data[2], 0, \
		ft_strchr_index(scene->pars.elem_data[2], '\n'));
		if (!sub)
			return (set_error_and_return(NULL, parsing_error, ERR_MEM_ALLOC));
		scene->light.bright = ft_atod(sub);
		free(sub);
	}
	else
		scene->light.bright = ft_atod(scene->pars.elem_data[2]);
	if (scene->light.bright < 0 || scene->light.bright > 1)
		return (set_error_and_return(NULL, parsing_error, \
		ERR_LIGHT_BRIGHTNESS));
	return (0);
}

static int	set_rgb_value_light(char *input_value, t_scene *scene, int rgb)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	if (rgb == 0)
		scene->light.color_r = value;
	else if (rgb == 1)
		scene->light.color_g = value;
	else if (rgb == 2)
		scene->light.color_b = value;
	return (0);
}

static int	light_color(t_scene *scene, char **rgb)
{
	int		value;

	value = 0;
	if (array_length(rgb) != 3 || rgb[2][0] == '\n')
		return (ERR_LIGHT_COLOR_FIELDS);
	if (!only_numbers_and_newline(rgb[0]) || !only_numbers_and_newline(rgb[1])
		|| !only_numbers_and_newline(rgb[2]))
		return (ERR_LIGHT_COLOR_VALUES);
	if (set_rgb_value_light(rgb[0], scene, 0) != 0)
		return (ERR_LIGHT_COLOR_VALUES);
	if (set_rgb_value_light(rgb[1], scene, 1) != 0)
		return (ERR_LIGHT_COLOR_VALUES);
	if (set_rgb_value_light(rgb[2], scene, 2) != 0)
		return (ERR_LIGHT_COLOR_VALUES);
	return (0);
}

int	parse_and_set_light(t_scene *scene)
{
	int		arr_len;
	char	**rgb;

	arr_len = array_length(scene->pars.elem_data);
	if (!correct_amt_of_fields(scene->pars.elem_data, 3)
		&& !correct_amt_of_fields(scene->pars.elem_data, 4))
		return (ERR_LIGHT_FIELDS);
	if (check_coordinates(scene->pars.elem_data[1], \
	&scene->pars.error_code, ERR_LIGHT_COOR_FIELDS) != 0)
		return (scene->pars.error_code);
	if (light_brightness(scene, &scene->pars.error_code) != 0)
		return (scene->pars.error_code);
	if (arr_len == 4 && scene->pars.elem_data[3][0] != '\n')
	{
		rgb = ft_split(scene->pars.elem_data[3], ',');
		if (!rgb)
			return (ERR_MEM_ALLOC);
		scene->pars.error_code = light_color(scene, rgb);
		ft_freearray(rgb);
		if (scene->pars.error_code != 0)
			return (scene->pars.error_code);
	}
	return (0);
}
