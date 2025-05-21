#include "main.h"

/*Checks if the coordinates of the given object are valid.
1. Checks if there are 3 coordinates.
2. Checks if the values only consists of numbers, '+' or '-' sign and 
a decimal point.
If an error occurs, the array of coordinates is freed and error code is set.*/
int	check_coordinates(char *input_coords, int *parsing_error, int error_code)
{
	char	**coords;

	coords = ft_split(input_coords, ',');
	if (!coords)
		return (set_error_and_return(NULL, &parsing_error, ERR_MEM_ALLOC));
	if (array_length(coords) != 3)
		return (set_error_and_return(coords, &parsing_error, error_code));
	if (!only_numbers_single_signs_and_dec_pt(coords[0])
		|| !only_numbers_single_signs_and_dec_pt(coords[1])
		|| !only_numbers_single_signs_and_dec_pt(coords[2]))
		return (set_error_and_return(coords, &parsing_error, error_code + 1));
	ft_freearray(coords);
	return (0);
}
