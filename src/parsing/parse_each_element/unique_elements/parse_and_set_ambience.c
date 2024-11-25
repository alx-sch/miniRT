/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_set_ambience.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:45:34 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:23:43 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parse_and_set_ambience(t_scene *scene)
{
	char	**rgb;

	if (!correct_amt_of_fields(scene->pars.elem_data, 3))
		return (ERR_AMB_FIELDS);
	scene->amb.light = ft_atod(scene->pars.elem_data[1]);
	if (scene->amb.light < 0.0 || scene->amb.light > 1.0)
		return (ERR_AMB_LIGHT);
	rgb = ft_split(scene->pars.elem_data[2], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	if (check_color(rgb, &scene->pars.error_code, ERR_AMB_COLOR_FIELDS) != 0)
	{
		ft_freearray(rgb);
		return (scene->pars.error_code);
	}
	set_color(rgb, &scene->amb.color_r, &scene->amb.color_g, \
	&scene->amb.color_b);
	ft_freearray(rgb);
	return (scene->pars.error_code);
}
