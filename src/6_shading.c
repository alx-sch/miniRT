/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_shading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:10:11 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/20 19:01:58 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Calculate the reflection of a vector off a surface.
 @param v_in			The incoming vector.
 @param surface_normal	The normal of the surface.

 @return The reflected vector.
*/
t_vec3	reflect(t_vec3 v_in, t_vec3 surface_normal)
{
	t_vec3	v_out;

	v_out = vec3_sub(\
		v_in, \
		vec3_scale(surface_normal, \
			2.0 * vec3_dot(v_in, surface_normal)));
	return (v_out);
}
