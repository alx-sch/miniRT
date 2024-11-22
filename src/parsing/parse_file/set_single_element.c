/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_single_element.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:32:43 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/22 15:17:03 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
