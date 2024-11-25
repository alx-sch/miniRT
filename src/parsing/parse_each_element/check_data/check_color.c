/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:29:46 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:04:52 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	check_rgb_value(char *input_value)
{
	int	value;

	value = ft_atoi(input_value);
	if (value < 0 || value > 255)
		return (1);
	return (0);
}

int	check_color(char **rgb, int *parsing_error, int error_code)
{
	if (array_length(rgb) != 3 || rgb[2][0] == '\n')
		return (set_error_and_return(NULL, parsing_error, error_code));
	if (!only_numbers_and_newline(rgb[0]) || !only_numbers_and_newline(rgb[1])
		|| !only_numbers_and_newline(rgb[2]))
		return (set_error_and_return(NULL, parsing_error, error_code + 1));
	if (check_rgb_value(rgb[0]) != 0 || check_rgb_value(rgb[1]) != 0
		|| check_rgb_value(rgb[2]) != 0)
		return (set_error_and_return(NULL, parsing_error, error_code + 1));
	return (0);
}
