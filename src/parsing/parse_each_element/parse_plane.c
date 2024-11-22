/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:50:27 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/22 15:46:32 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	check_plane_coordinates(t_scene *scene)
{
	char	**coords;

	coords = ft_split(scene->pars.elem_data[1], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	if (array_length(coords) != 3)
		return (ERR_PL_COOR_FIELDS);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (ERR_PL_COOR_VALUES);
	}
	ft_freearray(coords);
	return (0);
}

static int	check_plane_orientation_vector(t_scene *scene)
{
	char	**coords;

	coords = ft_split(scene->pars.elem_data[2], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	if (array_length(coords) != 3)
		return (ERR_PL_VECTOR_FIELDS);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (ERR_PL_VECTOR_VALUES);
	}
	if (ft_atod(coords[0]) < -1 || ft_atod(coords[0]) > 1
		|| ft_atod(coords[1]) < -1 || ft_atod(coords[1]) > 1
		|| ft_atod(coords[2]) < -1 || ft_atod(coords[2]) > 1)
	{
		ft_freearray(coords);
		return (ERR_PL_VECTOR_VALUES);
	}
	ft_freearray(coords);
	return (0);
}

static int	check_rgb_value_pl(char *input_value)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	return (0);
}

static int	check_plane_color(char **rgb)
{
	if (array_length(rgb) != 3 || rgb[2][0] == '\n')
		return (ERR_PL_COLOR_FIELDS);
	if (!only_numbers_and_newline(rgb[0]) || !only_numbers_and_newline(rgb[1])
		|| !only_numbers_and_newline(rgb[2]))
		return (ERR_PL_COLOR_VALUES);
	if (check_rgb_value_pl(rgb[0]) != 0)
		return (ERR_PL_COLOR_VALUES);
	if (check_rgb_value_pl(rgb[1]) != 0)
		return (ERR_PL_COLOR_VALUES);
	if (check_rgb_value_pl(rgb[2]) != 0)
		return (ERR_PL_COLOR_VALUES);
	return (0);
}

int	parse_plane(t_scene *scene)
{
	char	**rgb;

	scene->tot_pl++;
	rgb = NULL;
	if (!correct_amt_of_fields(scene->pars.elem_data, 4))
		return (ERR_PL_FIELDS);
	scene->pars.error_code = check_plane_coordinates(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	scene->pars.error_code = check_plane_orientation_vector(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	scene->pars.error_code = check_plane_color(rgb);
	ft_freearray(rgb);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	return (0);
}
