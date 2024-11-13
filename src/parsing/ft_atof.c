/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:05:04 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/13 17:59:10 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	get_decimals_before_dec_pt(char *str, int i)
{
	char	*decimal_str;
	int		dec_res;

	decimal_str = ft_substr(str, 0, i);
	dec_res = ft_atoi(decimal_str);
	free(decimal_str);
	return (dec_res);
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
	dec_res = get_decimals_before_dec_pt(str, i);
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
