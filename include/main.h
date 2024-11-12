/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/12 18:16:54 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>	// for read(), write()
# include <stdio.h>		// for printf(), perror()
# include <string.h>	// for strerror()
# include <stdlib.h>	// for malloc(), free(), exit()
# include <fcntl.h>		// for open()
# include "libft.h"

typedef struct s_pars
{
	int		a_found;
	int		c_found;
	int		l_found;
	int		fd;
	char	*element;
	char	**elem_data;
}	t_pars;

// PARSING
void	parsing(int argc, char **argv);
void	errors_parsing(int error_code);

#endif
