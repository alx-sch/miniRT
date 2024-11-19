/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:53:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/19 18:11:03 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	cylinder_coordinates(t_scene *scene)
{
	char	**coords;
	int		i;

	i = 0;
	coords = ft_split(scene->pars.elem_data[1], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	if (array_length(coords) != 3)
		return (ERR_CY_COOR_FIELDS);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (ERR_CY_COOR_VALUES);
	}
	scene->cy.x = ft_atod(coords[0]);
	scene->cy.y = ft_atod(coords[1]);
	scene->cy.z = ft_atod(coords[2]);
	ft_freearray(coords);
	return (0);
}

static int	cylinder_orientation_vector(t_scene *scene)
{
	char	**coords;
	int		i;

	i = 0;
	coords = ft_split(scene->pars.elem_data[2], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	if (array_length(coords) != 3)
		return (ERR_CY_VECTOR_FIELDS);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (ERR_CY_VECTOR_VALUES);
	}
	scene->cy.vec_x = ft_atod(coords[0]);
	scene->cy.vec_y = ft_atod(coords[1]);
	scene->cy.vec_z = ft_atod(coords[2]);
	ft_freearray(coords);
	if (scene->cy.vec_x < -1 || scene->cy.vec_x > 1
		|| scene->cy.vec_y < -1 || scene->cy.vec_y > 1
		|| scene->cy.vec_z < -1 || scene->cy.vec_z > 1)
		return (ERR_CY_VECTOR_VALUES);
	return (0);
}

static int	set_rgb_value_cy(char *input_value, t_scene *scene, int rgb)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	if (rgb == 0)
		scene->cy.color_r = value;
	else if (rgb == 1)
		scene->cy.color_g = value;
	else if (rgb == 2)
		scene->cy.color_b = value;
	return (0);
}

static int	cylinder_color(t_scene *scene, char **rgb)
{
	int		value;

	value = 0;
	if (array_length(rgb) != 3 || rgb[2][0] == '\n')
		return (ERR_CY_COLOR_FIELDS);
	if (!only_numbers_and_newline(rgb[0]) || !only_numbers_and_newline(rgb[1])
		|| !only_numbers_and_newline(rgb[2]))
		return (ERR_CY_COLOR_VALUES);
	if (set_rgb_value_cy(rgb[0], scene, 0) != 0)
		return (ERR_CY_COLOR_VALUES);
	if (set_rgb_value_cy(rgb[1], scene, 1) != 0)
		return (ERR_CY_COLOR_VALUES);
	if (set_rgb_value_cy(rgb[2], scene, 2) != 0)
		return (ERR_CY_COLOR_VALUES);
	return (0);
}

int	parse_cylinder(t_scene *scene)
{
	char	**rgb;

	if (!correct_amt_of_fields(scene->pars.elem_data, 6))
		return (ERR_CY_FIELDS);
	scene->pars.error_code = cylinder_coordinates(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	scene->pars.error_code = cylinder_orientation_vector(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[3]))
		return (ERR_CY_DM);
	scene->cy.dm = ft_atod(scene->pars.elem_data[3]);
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[4]))
		return (ERR_CY_HEIGHT);
	scene->cy.height = ft_atod(scene->pars.elem_data[4]);
	rgb = ft_split(scene->pars.elem_data[5], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	scene->pars.error_code = cylinder_color(scene, rgb);
	ft_freearray(rgb);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	return (0);
}
