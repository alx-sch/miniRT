/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:50:27 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:17:28 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parse_plane(t_scene *scene)
{
	char	**rgb;

	scene->tot_pl++;
	if (!correct_amt_of_fields(scene->pars.elem_data, 4))
		return (ERR_PL_FIELDS);
	if (check_coordinates(scene->pars.elem_data[1], \
	&scene->pars.error_code, ERR_PL_COOR_FIELDS) != 0)
		return (scene->pars.error_code);
	if (check_orientation_vector(scene->pars.elem_data[2], \
	&scene->pars.error_code, ERR_PL_VECTOR_FIELDS) != 0)
		return (scene->pars.error_code);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	if (check_color(rgb, &scene->pars.error_code, ERR_PL_COLOR_FIELDS) != 0)
	{
		ft_freearray(rgb);
		return (scene->pars.error_code);
	}
	ft_freearray(rgb);
	return (0);
}
