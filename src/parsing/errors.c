/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:52 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/13 14:41:20 by nholbroo         ###   ########.fr       */
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

void	errors_parsing(t_pars *parsing)
{
	if (parsing->error_code == 4)
		ft_putstr_fd("Error\nMemory allocation failure.\n", 2);
	if (parsing->error_code == 5)
		ft_putstr_fd("Error\nAmbience, camera and light source can only occure \
once. It must be written as a single 'A', 'C' or 'L'.\n", 2);
	if (parsing->error_code == 6)
		ft_putstr_fd("Error\n.rt-file can't be empty.\n", 2);
	free_parsing_and_exit(parsing);
}
