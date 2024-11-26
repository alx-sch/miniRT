/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/26 17:41:11 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// Standard C libraries
# include <unistd.h>		// for open(), close(), read(), write()
# include <stdio.h>			// for printf(), perror()
# include <string.h>		// for strerror()
# include <stdlib.h>		// for malloc(), free(), exit()
# include <errno.h>			// for errno
# include <fcntl.h>			// for open()
# include <math.h> 			// for math functions


// X11 library headers
# include <X11/keysym.h>	// Macros for key symbols, e.g. XK_Escape
# include <X11/X.h>			// Macros for event names, e.g. DestroyNotify

// Custom headers
# include "libft.h"			// libft
# include "mlx.h"			// mlx
# include "errors.h"		// Error messages and formatting styles
# include "types.h"			// All custom types and data structs, e.g. 't_rt'
# include "parsing.h"		// Parsing header file

//#############
//# CONSTANTS #
//#############

# define WINDOW_TITLE	"miniRT by Natalie Holbrook & Alex Schenk @42Berlin"

//##################
//# FCT PROTOTYPES #
//##################

// initialization.c

void	init_mlx(t_rt *rt);

// event_handlers.c

int		handle_keypress(int keycode, t_rt *rt);
int		handle_window_close(t_rt *rt);

// utils/cleanup.c

void	cleanup(t_rt **rt_ptr);

// utils/error_exit.c

void	cleanup_error_exit(char *msg, t_rt *rt);

// COLORS
# define COLOR_RED		"\033[31m"
# define COLOR_GREEN	"\033[32m"
# define COLOR_YELLOW	"\033[33m"
# define COLOR_BLUE		"\033[34m"
# define COLOR_MAGENTA	"\033[35m"
# define COLOR_CYAN		"\033[36m"
# define COLOR_WHITE	"\033[37m"
# define COLOR_BLACK	"\033[30m"
# define COLOR_RESET	"\033[0m"

/*
	GENERAL
*/

// GENERAL --FREE
void	free_parsing(t_pars *parsing);
int		ft_freearray(char **arr);
void	free_scene_and_exit(t_scene *scene);
void	free_scene(t_scene *scene);

// GENERAL -- UTILS
int		array_length(char **array);
double	ft_atod(char *str);
int		ft_strchr_index(char *str, char c);
int		only_numbers_and_newline(char *str);
int		only_numbers_dec_pt_and_newline(char *str);
int		only_numbers_single_signs_and_dec_pt(char *str);
int		only_numbers_and_dec_pt(char *str);

#endif
