/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse_and_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:58 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/25 19:08:30 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Checks if the camera's field of view is valid.
It can only consist of numbers and/or a newline character.
It can only be between 0 and 180. If an error occurs, sets the
right error code and returns that error code. Returns 0 upon success.*/
static int	camera_field_of_view(t_scene *scene, int *parsing_error)
{
	if (!only_numbers_and_newline(scene->pars.elem_data[3]))
		return (set_error_and_return(NULL, &parsing_error, \
		ERR_CAM_FIELD_OF_VIEW));
	scene->cam.fov = ft_atoi(scene->pars.elem_data[3]);
	if (scene->cam.fov < 0 || scene->cam.fov > 180)
		return (set_error_and_return(NULL, &parsing_error, \
		ERR_CAM_FIELD_OF_VIEW));
	return (0);
}

/*
    To avoid issues with gimbal lock and singularities in vector math,
    this function ensures the correct calculation of the 'camera right' vector.
    When the camera is looking directly up (0, 1, 0) or down (0, -1, 0),
    the standard cross product calculations for the right and up vectors fail
    because they become parallel or undefined. This would result in all rays
	being identical instead of spreading out.
	To fix this, we fall back to a default right vector when the cross product
	results in a zero vector.
*/
static t_vec3	set_camera_right(t_scene *scene)
{
	t_vec3	cam_right;

	cam_right = vec3_cross(vec3_new(0, 1, 0), scene->cam.dir);
	if (vec3_length(cam_right) < EPSILON)
		cam_right = vec3_new(1, 0, 0);
	return (vec3_norm(cam_right));
}

/*Parses and sets a camera object.
1. Checks if there's a correct amount of fields (4).
2. Checks if the coordinates are valid.
3. Checks if the orientation vector is valid.
4. Checks if the field of view is valid (between 0 and 180).
Sets all values and returns 0 upon success, and an error code upon error.*/
int	parse_and_set_camera(t_scene *scene)
{
	if (!correct_amt_of_fields(scene->pars.elem_data, 4))
		return (ERR_CAM_FIELDS);
	if (check_coordinates(scene->pars.elem_data[1], &scene->pars.error_code, \
	ERR_CAM_COOR_FIELDS) != 0)
		return (scene->pars.error_code);
	set_coordinates(scene->pars.elem_data[1], &scene->cam.pos.x, \
	&scene->cam.pos.y, &scene->cam.pos.z);
	if (check_orientation_vector(scene->pars.elem_data[2], \
	&scene->pars.error_code, ERR_CAM_VECTOR_FIELDS) != 0)
		return (scene->pars.error_code);
	set_orientation_vector(scene->pars.elem_data[2], &scene->cam.dir.x, \
	&scene->cam.dir.y, &scene->cam.dir.z);
	scene->cam.dir = vec3_norm(scene->cam.dir);
	if (camera_field_of_view(scene, &scene->pars.error_code) != 0)
		return (scene->pars.error_code);
	scene->cam.scale = tan((scene->cam.fov / 2) * M_PI / 180.0);
	scene->cam.aspect_ratio = (double)WINDOW_W / (double)WINDOW_H;
	scene->cam.right = set_camera_right(scene);
	scene->cam.up = vec3_norm(vec3_cross(\
							scene->cam.dir, \
				scene->cam.right));
	return (0);
}
