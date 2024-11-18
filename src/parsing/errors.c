/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:52 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 18:47:09 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	errors_file(int error_code)
{
	if (error_code == ERR_USAGE)
		ft_putstr_fd(ERR_MSG_USAGE, 2);
	else if (error_code == ERR_FILE_EXTENSION)
		ft_putstr_fd(ERR_MSG_FILE_EXTENSION, 2);
	else if (error_code == ERR_FILE_ACCESS)
		perror(ERR_MSG_FILE_ACCESS);
	exit(error_code);
}

void	errors_parsing(t_pars *parsing)
{
	if (parsing->error_code == ERR_MEM_ALLOC)
		ft_putstr_fd(ERR_MSG_MEM_ALLOC, 2);
	else if (parsing->error_code == ERR_UNIQUE_ELEM)
		ft_putstr_fd(ERR_MSG_UNIQUE_ELEM, 2);
	else if (parsing->error_code == ERR_FILE_EMPTY)
		ft_putstr_fd(ERR_MSG_FILE_EMPTY, 2);
	else if (parsing->error_code >= 7 && parsing->error_code <= 10)
		ambience_errors(parsing);
	else if (parsing->error_code >= 11 && parsing->error_code <= 16)
		camera_errors(parsing);
	else if (parsing->error_code >= 17 && parsing->error_code <= 22)
		light_errors(parsing);
	free_parsing_and_exit(parsing);
}
