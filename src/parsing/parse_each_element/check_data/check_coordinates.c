/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:37:57 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:01:35 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_coordinates(char *input_coords, int *parsing_error, int error_code)
{
	char	**coords;

	coords = ft_split(input_coords, ',');
	if (!coords)
		return (set_error_and_return(NULL, parsing_error, ERR_MEM_ALLOC));
	if (array_length(coords) != 3)
		return (set_error_and_return(coords, parsing_error, error_code));
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
		return (set_error_and_return(coords, parsing_error, error_code + 1));
	ft_freearray(coords);
	return (0);
}
