/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:22:32 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:24:36 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	allocate_nonunique_elements(t_scene *scene)
{
	int	i;

	i = 0;
	scene->pl = malloc(sizeof(t_pl) * scene->tot_pl);
	if (!scene->pl)
		return (1);
	while (i < scene->tot_pl)
		init_plane(&scene->pl[i++]);
	i = 0;
	scene->sp = malloc(sizeof(t_sp) * scene->tot_sp + 1);
	if (!scene->sp)
		return (1);
	while (i < scene->tot_sp)
		init_sphere(&scene->sp[i++]);
	i = 0;
	scene->cy = malloc(sizeof(t_cy) * scene->tot_cy + 1);
	if (!scene->cy)
		return (1);
	while (i < scene->tot_cy)
		init_cylinder(&scene->cy[i++]);
	return (0);
}

void	init_sphere(t_sp *sp)
{
	sp->x = 0;
	sp->y = 0;
	sp->z = 0;
	sp->dm = 0;
	sp->color_r = 0;
	sp->color_g = 0;
	sp->color_b = 0;
}

void	init_plane(t_pl *pl)
{
	pl->x = 0;
	pl->y = 0;
	pl->z = 0;
	pl->vec_x = 0;
	pl->vec_y = 0;
	pl->vec_z = 0;
	pl->color_r = 0;
	pl->color_g = 0;
	pl->color_b = 0;
}

void	init_cylinder(t_cy *cy)
{
	cy->x = 0;
	cy->y = 0;
	cy->z = 0;
	cy->vec_x = 0;
	cy->vec_y = 0;
	cy->vec_z = 0;
	cy->dm = 0;
	cy->height = 0;
	cy->color_r = 0;
	cy->color_g = 0;
	cy->color_b = 0;
}
