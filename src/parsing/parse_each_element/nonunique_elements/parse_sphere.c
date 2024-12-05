/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:18 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/05 13:30:16 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Parses a sphere object.
1. Checks if there's a correct amount of fields (4).
2. Checks if the coordinates are valid.
3. Checks if the diameter is valid.
4. Checks if the color values are valid.
Also keeps track of the count, ultimately storing the total count (how
many occurences of the object), to be able to allocate memory correctly
later on.
Returns 0 upon success, and an error code upon error.*/
int	parse_sphere(t_tmp_scene *scene)
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
	return (0);
}
