/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:18 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 19:34:25 by nholbroo         ###   ########.fr       */
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
	scene->sp.x = ft_atof(coords[0]);
	scene->sp.y = ft_atof(coords[1]);
	scene->sp.z = ft_atof(coords[2]);
	ft_freearray(coords);
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
	value = ft_atoi(rgb[0]);
	if (value < 0 || value > 255)
		return (ERR_SP_COLOR_VALUES);
	scene->sp.color_r = value;
	value = ft_atoi(rgb[1]);
	if (value < 0 || value > 255)
		return (ERR_SP_COLOR_VALUES);
	scene->sp.color_g = value;
	value = ft_atoi(rgb[2]);
	if (value < 0 || value > 255)
		return (ERR_SP_COLOR_VALUES);
	scene->sp.color_b = value;
	return (0);
}

static int	sphere_diameter(t_scene *scene)
{
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[2]))
		return (ERR_SP_DM);
	scene->sp.dm = ft_atof(scene->pars.elem_data[2]);
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
