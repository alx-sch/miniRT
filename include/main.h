/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/13 17:21:13 by nholbroo         ###   ########.fr       */
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
	int		error_code;
	char	*element;
	char	**elem_data;
}	t_pars;

typedef struct s_scene
{
	t_pars			pars;
	float			amb_light;
	unsigned char	amb_color;
	float			cam_x;
	float			cam_y;
	float			cam_z;
	float			cam_vec_x;
	float			cam_vec_y;
	float			cam_vec_z;
	int				cam_rov;
}	t_scene;

// PARSING
float	ft_atof(char *str);
void	parsing(int argc, char **argv);
int		check_file_existence(char *str);
int		check_file_extension(char *str);
void	init_parsing(t_pars *parsing);
void	init_scene(t_scene *scene);
int		parse_ambience(t_pars *parsing);
void	errors_file(int error_code);
void	errors_parsing(t_pars *pars);

// FREE
void	free_parsing_and_exit(t_pars *parsing);
int		ft_freearray(char **arr);

// UTILS
int		array_length(char **array);

#endif
