/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_parse_and_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:50:27 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/12 23:58:15 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/* Stores special attributes for a plane in the object data. */
static void	set_special_attributes_plane(t_scene *scene, t_obj *obj)
{
	obj->pl.ixd.difference = vec3_sub(obj->pl.point_in_plane, scene->cam.pos);
	obj->pl.hex_color = color_to_hex(obj->pl.color);
	obj->pl.ixd.dot_diff_normal = vec3_dot(obj->pl.ixd.difference, \
		obj->pl.normal);
}

/*Stores all the data of the current plane in the linked list of objects.*/
int	set_plane(t_scene *scene)
{
	t_obj	*obj;
	char	**rgb;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (ERR_MEM_ALLOC);
	obj->sp.object_type = PLANE;
	if (set_coordinates(scene->pars.elem_data[1], \
	&obj->pl.point_in_plane.x, &obj->pl.point_in_plane.y, \
	&obj->pl.point_in_plane.z) != 0)
		return (ERR_MEM_ALLOC);
	if (set_orientation_vector(scene->pars.elem_data[2], \
		&obj->pl.normal.x, &obj->pl.normal.y, &obj->pl.normal.z))
		return (ERR_MEM_ALLOC);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &obj->pl.color.r, &obj->pl.color.g, &obj->pl.color.b);
	set_special_attributes_plane(scene, obj);
	obj->pl.hit = 0;
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
	return (set_plane(scene));
}
