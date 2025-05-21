#include "main.h"

/*Frees the parsing struct.*/
void	free_parsing(t_pars *parsing)
{
	if (parsing)
	{
		if (parsing->element)
			free(parsing->element);
		if (parsing->elem_data)
			ft_freearray(parsing->elem_data);
	}
}
