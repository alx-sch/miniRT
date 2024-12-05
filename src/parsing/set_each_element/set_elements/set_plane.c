/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:50:27 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/05 13:27:38 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Sets a plane object.
1. Sets the input coordinates.
2. Sets the input orientation vector.
3. Sets the input color values.
Also keeps track of the count, so that the next time the function is called,
it will store the input in the next instance of the object.
Returns 0 upon success, and an error code upon memory allocation error.*/
int	set_plane(t_tmp_scene *scene, t_plane *pl)
{
	char	**rgb;

	rgb = NULL;
	if (set_coordinates(scene->pars.elem_data[1], &pl->point_in_plane.x, \
		&pl->point_in_plane.y, &pl->point_in_plane.z) != 0)
		return (ERR_MEM_ALLOC);
	if (set_orientation_vector(scene->pars.elem_data[2], \
	&pl->normal.x, &pl->normal.y, &pl->normal.z) != 0)
		return (ERR_MEM_ALLOC);
	rgb = ft_split(scene->pars.elem_data[3], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &pl->color.r, &pl->color.g, &pl->color.b);
	ft_freearray(rgb);
	scene->pars.pl_count++;
	return (0);
}
