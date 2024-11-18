/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:52 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 17:01:02 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	errors_file(int error_code)
{
	if (error_code == 1)
	{
		ft_putstr_fd("Error\nUsage: ./miniRT <scene.rt>\n", 2);
		exit(1);
	}
	if (error_code == 2)
	{
		ft_putstr_fd("Error\nFile extension must be of type '.rt'.\n", 2);
		exit(2);
	}
	if (error_code == 3)
	{
		perror("Error\nCan't access scene description file");
		exit(3);
	}
}

static void	ambience_errors(t_pars *parsing)
{
	if (parsing->error_code == 7)
		ft_putstr_fd("Error\nAmbient light must have 3 fields.\n", 2);
	if (parsing->error_code == 8)
		ft_putstr_fd("Error\nAmbient light must be between 0.0 and 1.0.\n", 2);
	if (parsing->error_code == 9)
		ft_putstr_fd("Error\nNeed 3 ambient color values.\n", 2);
	if (parsing->error_code == 10)
		ft_putstr_fd("Error\nAmbient color values must be between 0 and 255.\n\
", 2);
}

static void	camera_errors(t_pars *parsing)
{
	if (parsing->error_code == 11)
		ft_putstr_fd("Error\nCamera must have 4 fields.\n", 2);
	if (parsing->error_code == 12)
		ft_putstr_fd("Error\nNeed 3 camera coordinate values.\n", 2);
	if (parsing->error_code == 13)
		ft_putstr_fd("Error\nCamera coordinates must be within the range \
of a float.\n", 2);
	if (parsing->error_code == 14)
		ft_putstr_fd("Error\nNeed 3 camera orientation vector values.\n", 2);
	if (parsing->error_code == 15)
		ft_putstr_fd("Error\nCamera orientation vector values must be between \
-1 and 1.\n", 2);
	if (parsing->error_code == 16)
		ft_putstr_fd("Error\nCamera's horizontal field of view must be a number\
 between 0 and 180.\n", 2);
}

static void	light_errors(t_pars *parsing)
{
	if (parsing->error_code == 17)
		ft_putstr_fd("Error\nLight field must have 4 fields.\n", 2);
	if (parsing->error_code == 18)
		ft_putstr_fd("Error\nNeed 3 light coordinate values.\n", 2);
	if (parsing->error_code == 19)
		ft_putstr_fd("Error\nLight coordinates must be withing the range \
of a float\n", 2);
	if (parsing->error_code == 20)
		ft_putstr_fd("Error\nLight brightness must be between 0 and 1.\n", 2);
	if (parsing->error_code == 21)
		ft_putstr_fd("Error\nNeed 3 light color values\n", 2);
	if (parsing->error_code == 22)
		ft_putstr_fd("Error\nLight color values must be between 0 and 255.\n", \
2);
}

void	errors_parsing(t_pars *parsing)
{
	if (parsing->error_code == 4)
		ft_putstr_fd("Error\nMemory allocation failure.\n", 2);
	if (parsing->error_code == 5)
		ft_putstr_fd("Error\nAmbience, camera and light source can only occure \
once. It must be written as a single 'A', 'C' or 'L'.\n", 2);
	if (parsing->error_code == 6)
		ft_putstr_fd("Error\n.rt-file can't be empty.\n", 2);
	if (parsing->error_code >= 7 && parsing->error_code <= 10)
		ambience_errors(parsing);
	if (parsing->error_code >= 11 && parsing->error_code <= 16)
		camera_errors(parsing);
	if (parsing->error_code >= 17)
		light_errors(parsing);
	free_parsing_and_exit(parsing);
}
