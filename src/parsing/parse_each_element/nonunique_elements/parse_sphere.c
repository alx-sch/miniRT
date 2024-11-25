/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:18 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:17:37 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parse_sphere(t_scene *scene)
{
	char	**rgb;

	scene->tot_sp++;
	if (!correct_amt_of_fields(scene->pars.elem_data, 4))
		return (ERR_SP_FIELDS);
	if (check_coordinates(scene->pars.elem_data[1], &scene->pars.error_code, \
	ERR_SP_COOR_FIELDS) != 0)
		return (scene->pars.error_code);
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[2]))
		return (ERR_SP_DM);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	if (check_color(rgb, &scene->pars.error_code, ERR_SP_COLOR_FIELDS) != 0)
	{
		ft_freearray(rgb);
		return (scene->pars.error_code);
	}
	ft_freearray(rgb);
	return (0);
}
