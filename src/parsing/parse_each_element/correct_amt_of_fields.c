/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_amt_of_fields.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:47:53 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/19 18:17:50 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
