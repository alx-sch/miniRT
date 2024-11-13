/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:57:38 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/13 18:05:01 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	only_numbers_and_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	only_numbers_single_signs_and_dec_pt(char *str)
{
	int	i;

	i = 0;
	if (!str[1])
		return (0);
	if ((str[0] == '-' && (str[1] < '0' || str[1] > '9'))
		|| (str[0] == '+' && (str[1] < '0' || str[1] > '9')))
		return (0);
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+' && str[i] != '-'
			&& str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}
