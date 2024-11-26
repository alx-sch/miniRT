/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/25 18:38:37 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>	// for read(), write()
# include <stdio.h>		// for printf(), perror()
# include <string.h>	// for strerror()
# include <stdlib.h>	// for malloc(), free(), exit()
# include <fcntl.h>		// for open()
# include <math.h> 		// for math functions
# include "libft.h"
# include "parsing.h"

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
