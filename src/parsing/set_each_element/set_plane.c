/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:50:27 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/22 15:55:12 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	set_plane_coordinates(t_scene *scene, t_pl *pl)
{
	char	**coords;

	coords = ft_split(scene->pars.elem_data[1], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	pl->x = ft_atod(coords[0]);
	pl->y = ft_atod(coords[1]);
	pl->z = ft_atod(coords[2]);
	ft_freearray(coords);
	return (0);
}

static int	set_plane_orientation_vector(t_scene *scene, t_pl *pl)
{
	char	**coords;

	coords = ft_split(scene->pars.elem_data[2], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	pl->vec_x = ft_atod(coords[0]);
	pl->vec_y = ft_atod(coords[1]);
	pl->vec_z = ft_atod(coords[2]);
	ft_freearray(coords);
	return (0);
}

static int	set_rgb_value_pl(t_pl *pl, char *input_value, int rgb)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	if (rgb == 0)
		pl->color_r = value;
	else if (rgb == 1)
		pl->color_g = value;
	else if (rgb == 2)
		pl->color_b = value;
	return (0);
}

static int	set_plane_color(t_pl *pl, char **rgb)
{
	set_rgb_value_pl(pl, rgb[0], 0);
	set_rgb_value_pl(pl, rgb[1], 1);
	set_rgb_value_pl(pl, rgb[2], 2);
	return (0);
}

int	set_plane(t_scene *scene, t_pl *pl)
{
	char	**rgb;

	rgb = NULL;
	if (set_plane_coordinates(scene, pl) != 0)
		return (ERR_MEM_ALLOC);
	if (set_plane_orientation_vector(scene, pl) != 0)
		return (ERR_MEM_ALLOC);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_plane_color(pl, rgb);
	ft_freearray(rgb);
	scene->pars.pl_count++;
	return (0);
}
