/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_set_camera.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:58 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:11:30 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	camera_field_of_view(t_scene *scene, int *parsing_error)
{
	if (!only_numbers_and_newline(scene->pars.elem_data[3]))
		return (set_error_and_return(NULL, parsing_error, \
		ERR_CAM_FIELD_OF_VIEW));
	scene->cam.field = ft_atoi(scene->pars.elem_data[3]);
	if (scene->cam.field < 0 || scene->cam.field > 180)
		return (set_error_and_return(NULL, parsing_error, \
		ERR_CAM_FIELD_OF_VIEW));
	return (0);
}

int	parse_and_set_camera(t_scene *scene)
{
	if (!correct_amt_of_fields(scene->pars.elem_data, 4))
		return (ERR_CAM_FIELDS);
	if (check_coordinates(scene->pars.elem_data[1], &scene->pars.error_code, \
	ERR_CAM_COOR_FIELDS) != 0)
		return (scene->pars.error_code);
	set_coordinates(scene->pars.elem_data[1], &scene->cam.x, &scene->cam.y, \
	&scene->cam.z);
	if (check_orientation_vector(scene->pars.elem_data[2], \
	&scene->pars.error_code, ERR_CAM_VECTOR_FIELDS) != 0)
		return (scene->pars.error_code);
	set_orientation_vector(scene->pars.elem_data[2], \
	&scene->cam.vec_x, &scene->cam.vec_y, &scene->cam.vec_z);
	if (camera_field_of_view(scene, &scene->pars.error_code) != 0)
		return (scene->pars.error_code);
	return (0);
}
