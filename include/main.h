/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/13 23:25:46 by aschenk          ###   ########.fr       */
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

# include <errno.h>	// errno

// initialization.c

void	init_mlx(t_rt *rt);

// event_handlers.c

int		handle_keypress(int keycode, t_rt *rt);
int		handle_window_close(t_rt *rt);

// utils/cleanup.c

void	cleanup(t_rt **rt_ptr);

// utils/error_exit.c

void	cleanup_error_exit(char *msg, t_rt *rt);

#endif
