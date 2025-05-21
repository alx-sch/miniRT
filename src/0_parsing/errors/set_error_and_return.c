#include "main.h"

/*Frees an array if there is an array allocated, sets the error code correctly,
and returns the error code.*/
int	set_error_and_return(char **arr, int **parsing_error, int error_code)
{
	if (arr)
		ft_freearray(arr);
	**parsing_error = error_code;
	return (error_code);
}
