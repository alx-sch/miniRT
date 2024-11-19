/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:46:56 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/19 16:47:07 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_single_element(t_scene *scene)
{
	if (!scene->pars.elem_data[0])
		scene->pars.error_code = 0;
	else if (!ft_strcmp(scene->pars.elem_data[0], "A"))
		scene->pars.error_code = parse_ambience(scene);
	else if (!ft_strcmp(scene->pars.elem_data[0], "C"))
		scene->pars.error_code = parse_camera(scene);
	else if (!ft_strcmp(scene->pars.elem_data[0], "L"))
		scene->pars.error_code = parse_light(scene);
	else if (!ft_strcmp(scene->pars.elem_data[0], "sp"))
		scene->pars.error_code = parse_sphere(scene);
	else if (!ft_strcmp(scene->pars.elem_data[0], "pl"))
		scene->pars.error_code = parse_plane(scene);
	else if (!ft_strcmp(scene->pars.elem_data[0], "cy"))
		scene->pars.error_code = parse_cylinder(scene);
	else if (!ft_strcmp(scene->pars.elem_data[0], "\n"))
		scene->pars.error_code = 0;
	else
		scene->pars.error_code = ERR_INVALID_IDENTIFIER;
	return (scene->pars.error_code);
}
