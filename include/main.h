/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/12 17:05:36 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "settings.h"
# include "errors.h"
# include "types.h"	// All custom types and data structs, e.g. 't_rt'

# include "libft.h"			// libft
# include "mlx.h"			// mlx
# include <X11/keysym.h>	// Macros for key symbols, e.g. XK_Escape
# include <X11/X.h>	// Macros releated to the event names/masks, e.g. KeyPress

# include <unistd.h>	// for open(), close(), read(), write()
# include <stdio.h>		// for printf(), perror()
# include <string.h>	// for strerror()
# include <stdlib.h>	// for malloc(), free(), exit()

// init.c

void	init_mlx(t_rt *rt);

// free.c

void	free_rt(t_rt **rt_ptr);


// utils.c

void	msg_and_exit(char *msg, t_rt *rt);
void	perror_and_exit(char *msg, t_rt *rt);

#endif
