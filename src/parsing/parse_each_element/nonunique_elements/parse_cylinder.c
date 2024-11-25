/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:53:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 17:51:29 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parse_cylinder(t_scene *scene)
{
	char	**rgb;

	scene->tot_cy++;
	if (!correct_amt_of_fields(scene->pars.elem_data, 6))
		return (ERR_CY_FIELDS);
	if (check_coordinates(scene->pars.elem_data[1], \
	&scene->pars.error_code, ERR_CY_COOR_FIELDS) != 0)
		return (scene->pars.error_code);
	if (check_orientation_vector(scene->pars.elem_data[2], \
	&scene->pars.error_code, ERR_CY_VECTOR_FIELDS) != 0)
		return (scene->pars.error_code);
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[3]))
		return (ERR_CY_DM);
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[4]))
		return (ERR_CY_HEIGHT);
	rgb = ft_split(scene->pars.elem_data[5], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	if (check_color(rgb, &scene->pars.error_code, ERR_CY_COLOR_FIELDS) != 0)
	{
		ft_freearray(rgb);
		return (scene->pars.error_code);
	}
	ft_freearray(rgb);
	return (0);
}
