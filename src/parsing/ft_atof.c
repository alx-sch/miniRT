/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:05:04 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/13 17:06:25 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	only_numbers_single_signs_and_dec_pt(char *str)
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

static int	ft_strchr_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

float	ft_atof(char *str)
{
	int		i;
	int		dec_res;
	float	fract_res;
	float	power;

	if (!only_numbers_single_signs_and_dec_pt(str))
		return (-1);
	i = ft_strchr_index(str, '.') + 1;
	if (i == 0)
		return (ft_atoi(str));
	dec_res = ft_atoi(ft_substr(str, 0, i));
	if (dec_res < 0)
		dec_res *= -1;
	fract_res = 0;
	power = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fract_res = fract_res * 10 + (str[i] - '0');
		power *= 10;
		i++;
	}
	fract_res /= power;
	if (str[0] == '-')
		return ((dec_res + fract_res) * -1);
	return (dec_res + fract_res);
}
