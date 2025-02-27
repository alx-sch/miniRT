/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:47:25 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/27 15:22:08 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Checks if the rt-file exists, and has the required permissions.*/
int	check_file_existence(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

/*Checks if the file extension is '.rt'.
Returns 0 upon success.
Returns 1 if the file extension is incorrect.*/
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
