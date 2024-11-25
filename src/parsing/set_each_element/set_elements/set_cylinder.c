/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:53:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 17:14:07 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_cylinder(t_scene *scene, t_cy *cy)
{
	char	**rgb;

	rgb = NULL;
	if (set_coordinates(scene->pars.elem_data[1], &cy->x, &cy->y, &cy->z) != 0)
		return (ERR_MEM_ALLOC);
	if (set_orientation_vector(scene->pars.elem_data[2], \
	&cy->vec_x, &cy->vec_y, &cy->z) != 0)
		return (ERR_MEM_ALLOC);
	cy->dm = ft_atod(scene->pars.elem_data[3]);
	cy->height = ft_atod(scene->pars.elem_data[4]);
	rgb = ft_split(scene->pars.elem_data[5], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &cy->color_r, &cy->color_g, &cy->color_b);
	ft_freearray(rgb);
	scene->pars.cy_count++;
	return (0);
}
