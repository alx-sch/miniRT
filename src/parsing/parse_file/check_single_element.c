/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:46:56 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 17:16:28 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
Checks the current type identifier, and checks if everything is correct,
depending on the type. If the line is empty, it ignores it.
For unique identifiers -> ambience, camera and light -- it will both
be checked and the values will be saved.
For nonunique identifiers -> cylinder, plane and sphere -- it will only
be checked and the values will not be saved.
@param type_id The first field of each element, the type
identifier, like 'A', 'sp', etc.
@param scene->pars.error_code A variable in the parsing struct that stores
an error code. If the error code is not 0, the program will print an error
message and exit.*/
int	check_single_element(t_scene *scene)
{
	char	*type_id;

	type_id = scene->pars.elem_data[0];
	if (!type_id)
		scene->pars.error_code = 0;
	else if (!ft_strcmp(type_id, "A") || !ft_strcmp(type_id, "A\n"))
		scene->pars.error_code = parse_and_set_ambience(scene);
	else if (!ft_strcmp(type_id, "C") || !ft_strcmp(type_id, "C\n"))
		scene->pars.error_code = parse_and_set_camera(scene);
	else if (!ft_strcmp(type_id, "L") || !ft_strcmp(type_id, "L\n"))
		scene->pars.error_code = parse_and_set_light(scene);
	else if (!ft_strcmp(type_id, "sp") || !ft_strcmp(type_id, "sp\n"))
		scene->pars.error_code = parse_sphere(scene);
	else if (!ft_strcmp(type_id, "pl") || !ft_strcmp(type_id, "pl\n"))
		scene->pars.error_code = parse_plane(scene);
	else if (!ft_strcmp(type_id, "cy") || !ft_strcmp(type_id, "cy\n"))
		scene->pars.error_code = parse_cylinder(scene);
	else if (!ft_strcmp(type_id, "\n"))
		scene->pars.error_code = 0;
	else
		scene->pars.error_code = ERR_INVALID_IDENTIFIER;
	return (scene->pars.error_code);
}
