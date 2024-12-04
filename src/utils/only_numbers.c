/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:57:38 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/19 17:18:47 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Searches a string to see if it only consists of numbers, dec point and '\n'.
Returns 1 if there were only numbers, dec point and '\n'.
Returns 0 if something else was encountered.*/
int	only_numbers_dec_pt_and_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '\n' && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

/*Searches a string to see if it only consists of numbers and '\n'.
Returns 1 if there were only numbers and '\n'.
Returns 0 if something else was encountered.*/
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

/*Searches a string to see if it only consists of numbers, '-', '+' and decimal 
point.
Returns 1 if there were only numbers, '+', '-' and a decimal point.
Returns 0 if something else was encountered.*/
int	only_numbers_single_signs_and_dec_pt(char *str)
{
	int	i;

	i = 0;
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

/*Searches a string to see if it only consists of numbers and decimal point.
Returns 1 if there were only numbers and a decimal point.
Returns 0 if something else was encountered.*/
int	only_numbers_and_dec_pt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}
