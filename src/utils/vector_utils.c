/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:35:34 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/19 16:52:26 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	vec_length_squared(t_vec3 *vec)
{
	return (sqrt(vec->x) + sqrt(vec->y) + sqrt(vec->z));
}

double	vec_length(t_vec3 *vec)
{
	return (sqrt(vec_length_squared(vec)));
}
