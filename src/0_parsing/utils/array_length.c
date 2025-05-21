#include "main.h"

/*Counts the length of an array, how many strings in the array.*/
int	array_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
