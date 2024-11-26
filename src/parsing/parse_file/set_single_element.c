/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_single_element.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:32:43 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 17:18:07 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
Sets the values of the current type identifier, ONLY for nonunique
elements --> cylinder, plane and sphere. They have already been validated
at this point, so the values are simply getting stored.
If the current identifier is NOT cy, pl or sp -- it will be ignored.
@param type_id The first field of each element, the type
identifier, like 'pl', 'sp', etc.
@param scene->pars.error_code A variable in the parsing struct that stores
an error code. If the error code is not 0, the program will print an error
message and exit.*/
int	set_single_element(t_scene *scene)
{
	char	*type_id;

	type_id = scene->pars.elem_data[0];
	if (!type_id)
		scene->pars.error_code = 0;
	else if (!ft_strcmp(type_id, "sp") || !ft_strcmp(type_id, "sp\n"))
		scene->pars.error_code = set_sphere(scene, \
		&scene->sp[scene->pars.sp_count]);
	else if (!ft_strcmp(type_id, "pl") || !ft_strcmp(type_id, "pl\n"))
		scene->pars.error_code = set_plane(scene, \
		&scene->pl[scene->pars.pl_count]);
	else if (!ft_strcmp(type_id, "cy") || !ft_strcmp(type_id, "cy\n"))
		scene->pars.error_code = set_cylinder(scene, \
		&scene->cy[scene->pars.cy_count]);
	else
		scene->pars.error_code = 0;
	return (scene->pars.error_code);
}
