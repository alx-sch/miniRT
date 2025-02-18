/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_parse_and_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:18 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/18 00:31:26 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Stores all the data of the current sphere in the linked list of objects.*/
int	set_sphere(t_scene *scene)
{
	t_obj	*obj;
	char	**rgb;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (ERR_MEM_ALLOC);
	obj->object_type = SPHERE;
	if (set_coordinates(scene->pars.elem_data[1], &obj->x.sp.center.x, \
		&obj->x.sp.center.y, &obj->x.sp.center.z) != 0)
		return (ERR_MEM_ALLOC);
	obj->x.sp.radius = (ft_atod(scene->pars.elem_data[2]) / 2);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &obj->color.r, &obj->color.g, &obj->color.b);
	obj->hex_color = color_to_hex(obj->color);
	if (add_to_object_list(&scene, &obj) != 0)
		return (ERR_MEM_ALLOC);
	return (0);
}

/*Parses a sphere object.
1. Checks if there's a correct amount of fields (4).
2. Checks if the coordinates are valid.
3. Checks if the diameter is valid.
4. Checks if the color values are valid.
Also keeps track of the count, ultimately storing the total count (how
many occurences of the object), to be able to allocate memory correctly
later on.
Returns 0 upon success, and an error code upon error.*/
int	parse_sphere(t_scene *scene)
{
	char	**rgb;

	scene->pars.tot_sp++;
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
	return (set_sphere(scene));
}
