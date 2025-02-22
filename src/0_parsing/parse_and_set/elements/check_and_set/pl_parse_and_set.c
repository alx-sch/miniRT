/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_parse_and_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:50:27 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/22 12:03:49 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Stores all the data of the current plane in the linked list of objects.*/
int	set_plane(t_scene *scene)
{
	t_obj	*obj;
	char	**rgb;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (ERR_MEM_ALLOC);
	obj->object_type = PLANE;
	if (set_coordinates(scene->pars.elem_data[1], \
	&obj->x.pl.point_in_plane.x, &obj->x.pl.point_in_plane.y, \
	&obj->x.pl.point_in_plane.z) != 0)
		return (ERR_MEM_ALLOC);
	if (set_orientation_vector(scene->pars.elem_data[2], \
		&obj->x.pl.normal.x, &obj->x.pl.normal.y, &obj->x.pl.normal.z))
		return (ERR_MEM_ALLOC);
	obj->x.pl.normal = vec3_norm(obj->x.pl.normal);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &obj->color.r, &obj->color.g, &obj->color.b);
	if (add_to_object_list(&scene, &obj) != 0)
		return (ERR_MEM_ALLOC);
	return (0);
}

/*Parses a plane object.
1. Checks if there's a correct amount of fields (4).
2. Checks if the coordinates are valid.
3. Checks if the orientation vector is valid.
4. Checks if the color values are valid.
Also keeps track of the count, ultimately storing the total count (how
many occurences of the object), to be able to allocate memory correctly
later on.
Returns 0 upon success, and an error code upon error.*/
int	parse_plane(t_scene *scene)
{
	char	**rgb;

	scene->pars.tot_pl++;
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
	return (set_plane(scene));
}
