/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_amt_of_fields.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:47:53 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/22 13:48:05 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
Checks if the type id (ambience, light, etc) has the correct amount of fields,
also taking a potential newline into account, e.g.:
A 0.0,1.0,42.0 0.9     
(This example would end with a newline since there are spaces after last field,
this function also takes care of this.)
@param len The length of the array (how many fields). When it is used with
-1, it's to adjust it to index instead of length.
@param expected_len How many fields is the element supposed to have.*/
int	correct_amt_of_fields(char **arr, int expected_len)
{
	int	len;

	len = array_length(arr);
	if (!ft_strcmp(arr[len - 1], "\n"))
	{
		if (len - 1 == expected_len)
			return (1);
		else
			return (0);
	}
	else if (len != expected_len)
		return (0);
	return (1);
}
