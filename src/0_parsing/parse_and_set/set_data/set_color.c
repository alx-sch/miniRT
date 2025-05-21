#include "main.h"

/*Sets the color values of an object.*/
void	set_color(char **rgb, unsigned char *r, unsigned char *g, \
unsigned char *b)
{
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	ft_freearray(rgb);
}
