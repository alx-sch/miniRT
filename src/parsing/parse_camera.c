/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:58 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 18:17:34 by nholbroo         ###   ########.fr       */
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
		return (ERR_MEM_ALLOC);
	if (array_length(coords) != 3)
		return (ERR_CAM_COOR_FIELDS);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (ERR_CAM_COOR_VALUES);
	}
	scene->cam.x = ft_atof(coords[0]);
	scene->cam.y = ft_atof(coords[1]);
	scene->cam.z = ft_atof(coords[2]);
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
		return (ERR_MEM_ALLOC);
	if (array_length(coords) != 3)
		return (ERR_CAM_VECTOR_FIELDS);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
	{
		ft_freearray(coords);
		return (ERR_CAM_VECTOR_VALUES);
	}
	scene->cam.vec_x = ft_atof(coords[0]);
	scene->cam.vec_y = ft_atof(coords[1]);
	scene->cam.vec_z = ft_atof(coords[2]);
	ft_freearray(coords);
	if (scene->cam.vec_x < -1 || scene->cam.vec_x > 1
		|| scene->cam.vec_y < -1 || scene->cam.vec_y > 1
		|| scene->cam.vec_z < -1 || scene->cam.vec_z > 1)
		return (ERR_CAM_VECTOR_VALUES);
	return (0);
}

static int	camera_field_of_view(t_scene *scene)
{
	if (!only_numbers_and_newline(scene->pars.elem_data[3]))
		return (ERR_CAM_FIELD_OF_VIEW);
	scene->cam.field = ft_atoi(scene->pars.elem_data[3]);
	if (scene->cam.field < 0 || scene->cam.field > 180)
		return (ERR_CAM_FIELD_OF_VIEW);
	return (0);
}

int	parse_camera(t_scene *scene)
{
	if (array_length(scene->pars.elem_data) != 4)
		return (ERR_CAM_FIELDS);
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
