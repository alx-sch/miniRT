/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:45:34 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/13 17:10:51 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parse_ambience(t_pars *parsing)
{
	float	ambience_lighting;

	if (array_length(parsing->elem_data) != 3)
		return (1);
	ambience_lighting = ft_atof(parsing->elem_data[1]);
	if (ambience_lighting < 0.0 || ambience_lighting > 1.0)
		return (1);
	printf("%f\n", ambience_lighting);
	return (0);
}
