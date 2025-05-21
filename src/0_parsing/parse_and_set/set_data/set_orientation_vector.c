#include "main.h"

/*Sets the orientation vector of an object.*/
int	set_orientation_vector(char *input_coords, double *x, double *y, double *z)
{
	char	**coords;

	coords = ft_split(input_coords, ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	*x = ft_atod(coords[0]);
	*y = ft_atod(coords[1]);
	*z = ft_atod(coords[2]);
	ft_freearray(coords);
	return (0);
}
