#include "main.h"

/*Searches a string for a char c, returns the index where it was found, 
if not found it returns -1.*/
int	ft_strchr_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
