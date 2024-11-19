/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:18 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/19 16:37:46 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	sphere_coordinates(t_scene *scene)
{
	char	**coords;
	int		i;

	i = 0;
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
	scene->sp.x = ft_atod(coords[0]);
	scene->sp.y = ft_atod(coords[1]);
	scene->sp.z = ft_atod(coords[2]);
	ft_freearray(coords);
	return (0);
}

static int	set_rgb_value_sp(char *input_value, t_scene *scene, int rgb)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	if (rgb == 0)
		scene->sp.color_r = value;
	else if (rgb == 1)
		scene->sp.color_g = value;
	else if (rgb == 2)
		scene->sp.color_b = value;
	return (0);
}

static int	sphere_color(t_scene *scene, char **rgb)
{
	int		value;

	value = 0;
	if (array_length(rgb) != 3)
		return (ERR_SP_COLOR_FIELDS);
	if (!only_numbers_and_newline(rgb[0]) || !only_numbers_and_newline(rgb[1])
		|| !only_numbers_and_newline(rgb[2]))
		return (ERR_SP_COLOR_VALUES);
	if (set_rgb_value_sp(rgb[0], scene, 0) != 0)
		return (ERR_SP_COLOR_VALUES);
	if (set_rgb_value_sp(rgb[1], scene, 1) != 0)
		return (ERR_SP_COLOR_VALUES);
	if (set_rgb_value_sp(rgb[2], scene, 2) != 0)
		return (ERR_SP_COLOR_VALUES);
	return (0);
}

static int	sphere_diameter(t_scene *scene)
{
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[2]))
		return (ERR_SP_DM);
	scene->sp.dm = ft_atod(scene->pars.elem_data[2]);
	return (0);
}

int	parse_sphere(t_scene *scene)
{
	char	**rgb;

	rgb = NULL;
	if (array_length(scene->pars.elem_data) != 4)
		return (ERR_SP_FIELDS);
	scene->pars.error_code = sphere_coordinates(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	scene->pars.error_code = sphere_diameter(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	scene->pars.error_code = sphere_color(scene, rgb);
	ft_freearray(rgb);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	return (0);
}
