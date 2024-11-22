/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:53:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/22 15:12:03 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	set_cylinder_coordinates(t_scene *scene, t_cy *cy)
{
	char	**coords;

	coords = ft_split(scene->pars.elem_data[1], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	cy->x = ft_atod(coords[0]);
	cy->y = ft_atod(coords[1]);
	cy->z = ft_atod(coords[2]);
	ft_freearray(coords);
	return (0);
}

static int	set_cylinder_orientation_vector(t_scene *scene, t_cy *cy)
{
	char	**coords;
	int		i;

	i = 0;
	coords = ft_split(scene->pars.elem_data[2], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	cy->vec_x = ft_atod(coords[0]);
	cy->vec_y = ft_atod(coords[1]);
	cy->vec_z = ft_atod(coords[2]);
	ft_freearray(coords);
	return (0);
}

static int	set_rgb_value_cy(t_cy *cy, char *input_value, int rgb)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	if (rgb == 0)
		cy->color_r = value;
	else if (rgb == 1)
		cy->color_g = value;
	else if (rgb == 2)
		cy->color_b = value;
	return (0);
}

static int	set_cylinder_color(t_cy *cy, char **rgb)
{
	set_rgb_value_cy(cy, rgb[0], 0);
	set_rgb_value_cy(cy, rgb[1], 1);
	set_rgb_value_cy(cy, rgb[2], 2);
	return (0);
}

int	set_cylinder(t_scene *scene, t_cy *cy)
{
	char	**rgb;

	rgb = NULL;
	if (set_cylinder_coordinates(scene, cy) != 0)
		return (ERR_MEM_ALLOC);
	if (set_cylinder_orientation_vector(scene, cy) != 0)
		return (ERR_MEM_ALLOC);
	cy->dm = ft_atod(scene->pars.elem_data[3]);
	cy->height = ft_atod(scene->pars.elem_data[4]);
	rgb = ft_split(scene->pars.elem_data[5], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_cylinder_color(cy, rgb);
	ft_freearray(rgb);
	scene->pars.cy_count++;
	return (0);
}
