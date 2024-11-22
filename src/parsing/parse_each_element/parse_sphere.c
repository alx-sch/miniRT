/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:18 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/22 15:46:48 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	check_sphere_coordinates(t_scene *scene)
{
	char	**coords;

	coords = ft_split(scene->pars.elem_data[1], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	if (array_length(coords) != 3)
		return (ERR_SP_COOR_FIELDS);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (ERR_SP_COOR_VALUES);
	}
	ft_freearray(coords);
	return (0);
}

static int	check_rgb_value_sp(char *input_value)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	return (0);
}

static int	check_sphere_color(char **rgb)
{
	int		value;

	value = 0;
	if (array_length(rgb) != 3 || rgb[2][0] == '\n')
		return (ERR_SP_COLOR_FIELDS);
	if (!only_numbers_and_newline(rgb[0]) || !only_numbers_and_newline(rgb[1])
		|| !only_numbers_and_newline(rgb[2]))
		return (ERR_SP_COLOR_VALUES);
	if (check_rgb_value_sp(rgb[0]) != 0)
		return (ERR_SP_COLOR_VALUES);
	if (check_rgb_value_sp(rgb[1]) != 0)
		return (ERR_SP_COLOR_VALUES);
	if (check_rgb_value_sp(rgb[2]) != 0)
		return (ERR_SP_COLOR_VALUES);
	return (0);
}

int	parse_sphere(t_scene *scene)
{
	char	**rgb;

	scene->tot_sp++;
	rgb = NULL;
	if (!correct_amt_of_fields(scene->pars.elem_data, 4))
		return (ERR_SP_FIELDS);
	scene->pars.error_code = check_sphere_coordinates(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[2]))
		return (ERR_SP_DM);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	scene->pars.error_code = check_sphere_color(rgb);
	ft_freearray(rgb);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	return (0);
}
