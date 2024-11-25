/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_orientation_vector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:33:28 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:02:38 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	orientation_vector_valid(char **coords)
{
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2])
		|| ft_atod(coords[0]) < -1 || ft_atod(coords[0]) > 1
		|| ft_atod(coords[1]) < -1 || ft_atod(coords[1]) > 1
		|| ft_atod(coords[2]) < -1 || ft_atod(coords[2]) > 1)
		return (0);
	return (1);
}

int	check_orientation_vector(char *input_coords, int *parsing_error, \
int error_code)
{
	char	**coords;

	coords = ft_split(input_coords, ',');
	if (!coords)
		return (set_error_and_return(NULL, parsing_error, ERR_MEM_ALLOC));
	if (array_length(coords) != 3)
		return (set_error_and_return(coords, parsing_error, error_code));
	if (!orientation_vector_valid(coords))
		return (set_error_and_return(coords, parsing_error, error_code));
	ft_freearray(coords);
	return (0);
}
