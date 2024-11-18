/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:58 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 16:05:33 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	camera_coordinates(t_scene *scene)
{
	char	**coords;
	int		i;

	i = 0;
	coords = ft_split(scene->pars.elem_data[1], ',');
	if (!coords)
		return (4);
	if (array_length(coords) != 3)
		return (12);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (13);
	}
	scene->cam_x = ft_atof(coords[0]);
	scene->cam_y = ft_atof(coords[1]);
	scene->cam_z = ft_atof(coords[2]);
	ft_freearray(coords);
	return (0);
}

static int	camera_orientation_vector(t_scene *scene)
{
	char	**coords;
	int		i;

	i = 0;
	coords = ft_split(scene->pars.elem_data[2], ',');
	if (!coords)
		return (4);
	if (array_length(coords) != 3)
		return (14);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (15);
	}
	scene->cam_vec_x = ft_atof(coords[0]);
	scene->cam_vec_y = ft_atof(coords[1]);
	scene->cam_vec_z = ft_atof(coords[2]);
	ft_freearray(coords);
	if (scene->cam_vec_x < -1 || scene->cam_vec_x > 1
		|| scene->cam_vec_y < -1 || scene->cam_vec_y > 1
		|| scene->cam_vec_z < -1 || scene->cam_vec_z > 1)
		return (15);
	return (0);
}

static int	camera_field_of_view(t_scene *scene)
{
	if (!only_numbers_and_newline(scene->pars.elem_data[3]))
		return (16);
	scene->cam_hfov = ft_atoi(scene->pars.elem_data[3]);
	if (scene->cam_hfov < 0 || scene->cam_hfov > 180)
		return (16);
	return (0);
}

int	parse_camera(t_scene *scene)
{
	if (array_length(scene->pars.elem_data) != 4)
		return (11);
	scene->pars.error_code = camera_coordinates(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	scene->pars.error_code = camera_orientation_vector(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	scene->pars.error_code = camera_field_of_view(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	return (0);
}
