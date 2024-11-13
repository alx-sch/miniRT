/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:45:34 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/13 17:39:05 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parse_ambience(t_scene *scene)
{
	if (array_length(scene->pars.elem_data) != 3)
		return (1);
	scene->amb_light = ft_atof(scene->pars.elem_data[1]);
	if (scene->amb_light < 0.0 || scene->amb_light > 1.0)
		return (1);
	printf("%f\n", scene->amb_light);
	return (0);
}
