/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:47:25 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/13 14:15:50 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_file_existence(char *str)
{
	if (access(str, R_OK) != 0)
		return (1);
	return (0);
}

int	check_file_extension(char *str)
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
