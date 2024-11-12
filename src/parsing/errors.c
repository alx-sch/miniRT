/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:52 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/12 16:40:07 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	errors_parsing(int error_code)
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
