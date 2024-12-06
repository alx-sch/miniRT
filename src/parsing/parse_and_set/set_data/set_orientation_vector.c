/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_orientation_vector.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:57:56 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 17:18:48 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Sets the orientation vector of an object.*/
int	set_orientation_vector(char *input_coords, double *x, double *y, double *z)
{
	char	**coords;
	int		i;

	i = 0;
	coords = ft_split(input_coords, ',');
	if (!coords)
		return (ERR_MEM_ALLOC);
	*x = ft_atod(coords[0]);
	*y = ft_atod(coords[1]);
	*z = ft_atod(coords[2]);
	ft_freearray(coords);
	return (0);
}
