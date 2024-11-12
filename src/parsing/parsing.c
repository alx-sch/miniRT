/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:47 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/12 16:39:34 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	check_file_existence(char *str)
{
	if (access(str, R_OK) != 0)
		return (1);
	return (0);
}

static int	check_file_extension(char *str)
{
	int	end;

	end = ft_strlen(str);
	if (end < 4)
		return (1);
	if (str[end - 1] != 't')
		return (1);
	if (str[end - 2] != 'r')
		return (1);
	if (str[end - 3] != '.')
		return (1);
	return (0);
}

void	parsing(int argc, char **argv)
{
	if (argc != 2)
		errors_parsing(1);
	if (check_file_extension(argv[1]))
		errors_parsing(2);
	if (check_file_existence(argv[1]))
		errors_parsing(3);
}
