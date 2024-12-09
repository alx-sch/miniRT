/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_orientation_vector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:33:28 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 16:58:31 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Checks if the values only consist of '+', '-', numbers and decimal point, 
if they are all between -1 and 1, and the if the vector is normalized.*/
static int	orientation_vector_valid(char **coords)
{
	double	vec_x;
	double	vec_y;
	double	vec_z;

	vec_x = ft_atod(coords[0]);
	vec_y = ft_atod(coords[1]);
	vec_z = ft_atod(coords[2]);
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2])
		|| vec_x < -1 || vec_x > 1
		|| vec_y < -1 || vec_y > 1
		|| vec_z < -1 || vec_z > 1)
		return (1);
	if (fabs(sqrt(vec_x * vec_x + vec_y * vec_y + vec_z * vec_z) - 1) > 0.0001)
		return (2);
	return (0);
}

/*Checks if the orientation vector of a given object is valid.
1. Checks if there are 3 coordinates.
2. Calls orientation_vector_valid() to see if the values only consist of 
'+', '-', numbers and decimal point, if they are all between -1 and 1, and
the if the vector is normalized.
If an error occurs, the correct error code is set.*/
int	check_orientation_vector(char *input_coords, int *parsing_error, \
int error_code)
{
	char	**coords;
	int		error;

	error = 0;
	coords = ft_split(input_coords, ',');
	if (!coords)
		return (set_error_and_return(NULL, &parsing_error, ERR_MEM_ALLOC));
	if (array_length(coords) != 3)
		return (set_error_and_return(coords, &parsing_error, error_code));
	error = orientation_vector_valid(coords);
	if (error == 1)
		return (set_error_and_return(coords, &parsing_error, error_code + 1));
	else if (error == 2)
		return (set_error_and_return(coords, &parsing_error, error_code + 2));
	ft_freearray(coords);
	return (0);
}
