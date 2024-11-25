/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unique_identifier.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:41:43 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:27:38 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	all_necessary_identifiers(t_pars *pars)
{
	if (pars->a_found && pars->c_found && pars->l_found)
		return (1);
	return (0);
}

static int	is_nonunique_identifier(char *str)
{
	if (!ft_strcmp(str, "sp") || !ft_strcmp(str, "sp\n")
		|| !ft_strcmp(str, "pl") || !ft_strcmp(str, "pl\n")
		|| !ft_strcmp(str, "cy") || !ft_strcmp(str, "cy\n"))
		return (1);
	return (0);
}

int	check_unique_identifier(t_pars *parsing, char *str)
{
	if (!str || is_nonunique_identifier(str))
		return (0);
	if (!ft_strcmp(str, "A") || !ft_strcmp(str, "A\n"))
	{
		if (parsing->a_found)
			return (1);
		else
			parsing->a_found = 1;
	}
	else if (!ft_strcmp(str, "C") || !ft_strcmp(str, "C\n"))
	{
		if (parsing->c_found)
			return (1);
		else
			parsing->c_found = 1;
	}
	else if (!ft_strcmp(str, "L") || !ft_strcmp(str, "L\n"))
	{
		if (parsing->l_found)
			return (1);
		else
			parsing->l_found = 1;
	}
	return (0);
}
