/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:50:27 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 17:14:38 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_plane(t_scene *scene, t_pl *pl)
{
	char	**rgb;

	rgb = NULL;
	if (set_coordinates(scene->pars.elem_data[1], &pl->x, &pl->y, &pl->z) != 0)
		return (ERR_MEM_ALLOC);
	if (set_orientation_vector(scene->pars.elem_data[2], \
	&pl->vec_x, &pl->vec_y, &pl->vec_z) != 0)
		return (ERR_MEM_ALLOC);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &pl->color_r, &pl->color_g, &pl->color_b);
	ft_freearray(rgb);
	scene->pars.pl_count++;
	return (0);
}
