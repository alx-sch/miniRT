/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_parse_and_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:18 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/24 15:51:28 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Stores all the data of the current sphere in the linked list of objects.*/
int	set_sphere(t_scene *scene)
{
	t_obj_data	*obj_data;
	char		**rgb;

	obj_data = malloc(sizeof(t_obj_data));
	if (!obj_data)
		return (ERR_MEM_ALLOC);
	obj_data->sp.object_type = SPHERE;
	if (set_coordinates(scene->pars.elem_data[1], &obj_data->sp.center.x, \
		&obj_data->sp.center.y, &obj_data->sp.center.z) != 0)
		return (ERR_MEM_ALLOC);
	obj_data->sp.radius = (ft_atod(scene->pars.elem_data[2]) / 2);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &obj_data->sp.color.r, &obj_data->sp.color.g, \
	&obj_data->sp.color.b);
	obj_data->sp.ixd.oc = vec3_sub(scene->cam.pos, obj_data->sp.center);
	obj_data->sp.ixd.c = vec3_dot(obj_data->sp.ixd.oc, \
	obj_data->sp.ixd.oc) - (obj_data->sp.radius * obj_data->sp.radius);
	if (add_to_object_list(&scene, &obj_data) != 0)
		return (ERR_MEM_ALLOC);
	obj_data->sp.hex_color = color_to_hex(obj_data->sp.color);
	obj_data->sp.hit = 0;
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

	scene->tot_sp++;
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
