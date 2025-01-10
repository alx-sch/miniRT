/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:00:45 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/10 17:13:20 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// double	clamp(double value, double min, double max)
// {
// 	if (value < min)
// 		return (min);
// 	if (value > max)
// 		return (max);
// 	return (value);
// }

// t_color	mix_ambient_light(t_color object_color, t_color ambient_color, \
// 	double ambient_intensity)
// {
// 	t_color	result;

// 	result.r = clamp(ambient_intensity * object_color.r * \
// 	ambient_color.r, 0.0, 1.0);
// 	result.g = clamp(ambient_intensity * object_color.g * \
// 	ambient_color.g, 0.0, 1.0);
// 	result.b = clamp(ambient_intensity * object_color.b * \
// 	ambient_color.b, 0.0, 1.0);
// 	return (result);
// }

/*Sets the color values of an object.*/
void	set_color(char **rgb, unsigned char *r, unsigned char *g, \
unsigned char *b)
{
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	ft_freearray(rgb);
}
