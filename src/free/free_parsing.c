/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:19:24 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/22 15:21:05 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
