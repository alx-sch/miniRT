/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:18 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 17:15:41 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_sphere(t_scene *scene, t_sp *sp)
{
	char	**rgb;

	rgb = NULL;
	if (set_coordinates(scene->pars.elem_data[1], &sp->x, &sp->y, &sp->z) != 0)
		return (ERR_MEM_ALLOC);
	sp->dm = ft_atod(scene->pars.elem_data[2]);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &sp->color_r, &sp->color_g, &sp->color_b);
	ft_freearray(rgb);
	scene->pars.sp_count++;
	return (0);
}
