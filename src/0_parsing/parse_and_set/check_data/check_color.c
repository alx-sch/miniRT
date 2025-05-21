#include "main.h"

/*Checks if the current value is greater than or equal to 0 or 
less than 255.
Returns 0 if it is within the range.
Returns 1 if it's too small or too big.*/
static int	check_rgb_value(char *input_value)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	return (0);
}

/*Checks if the rgb values of the given object are valid.
1. Checks if there are 3 values.
2. Checks if they all consist of only numbers and/or a newline (as the last
number will be followed by a newline).
3. Checks if they are all in range of 0 to 255.
If an error occurs, a correct error code is set.*/
int	check_color(char **rgb, int *parsing_error, int error_code)
{
	if (array_length(rgb) != 3 || rgb[2][0] == '\n')
		return (set_error_and_return(NULL, &parsing_error, error_code));
	if (!only_numbers_and_newline(rgb[0]) || !only_numbers_and_newline(rgb[1])
		|| !only_numbers_and_newline(rgb[2]))
		return (set_error_and_return(NULL, &parsing_error, error_code + 1));
	if (check_rgb_value(rgb[0]) != 0 || check_rgb_value(rgb[1]) != 0
		|| check_rgb_value(rgb[2]) != 0)
		return (set_error_and_return(NULL, &parsing_error, error_code + 1));
	return (0);
}
