/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:18 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/22 15:07:22 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	set_sphere_coordinates(t_scene *scene, t_sp *sp)
{
	char	**coords;

	coords = ft_split(scene->pars.elem_data[1], ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	sp->x = ft_atod(coords[0]);
	sp->y = ft_atod(coords[1]);
	sp->z = ft_atod(coords[2]);
	ft_freearray(coords);
	return (0);
}

static int	set_rgb_value_sp(t_sp *sp, char *input_value, int rgb)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	if (rgb == 0)
		sp->color_r = value;
	else if (rgb == 1)
		sp->color_g = value;
	else if (rgb == 2)
		sp->color_b = value;
	return (0);
}

static int	set_sphere_color(t_sp *sp, char **rgb)
{
	set_rgb_value_sp(sp, rgb[0], 0);
	set_rgb_value_sp(sp, rgb[1], 1);
	set_rgb_value_sp(sp, rgb[2], 2);
	return (0);
}

int	set_sphere(t_scene *scene, t_sp *sp)
{
	char	**rgb;

	rgb = NULL;
	if (set_sphere_coordinates(scene, sp) != 0)
		return (ERR_MEM_ALLOC);
	sp->dm = ft_atod(scene->pars.elem_data[2]);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_sphere_color(sp, rgb);
	ft_freearray(rgb);
	scene->pars.sp_count++;
	return (0);
}
