/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/18 17:14:51 by nholbroo         ###   ########.fr       */
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

typedef struct s_ambience
{
	float			light;
	unsigned char	color_r;
	unsigned char	color_g;
	unsigned char	color_b;
}	t_amb;

typedef struct s_camera
{
	float			x;
	float			y;
	float			z;
	float			vec_x;
	float			vec_y;
	float			vec_z;
	unsigned char	field;
}	t_cam;

typedef struct s_light
{
	float			x;
	float			y;
	float			z;
	float			bright;
	unsigned char	color_r;
	unsigned char	color_g;
	unsigned char	color_b;
}	t_light;


typedef struct s_scene
{
	t_pars			pars;
	float			amb_light;
	unsigned char	amb_color_r;
	unsigned char	amb_color_g;
	unsigned char	amb_color_b;
	float			cam_x;
	float			cam_y;
	float			cam_z;
	float			cam_vec_x;
	float			cam_vec_y;
	float			cam_vec_z;
	unsigned char	cam_hfov;
	float			light_x;
	float			light_y;
	float			light_z;
	float			light_bright;
	unsigned char	light_color_r;
	unsigned char	light_color_g;
	unsigned char	light_color_b;
}	t_scene;

// PARSING
float	ft_atof(char *str);
void	parsing(int argc, char **argv);
int		check_file_existence(char *str);
int		check_file_extension(char *str);
void	init_parsing(t_pars *parsing);
void	init_scene(t_scene *scene);
void	init_ambience(t_amb *amb);
void	init_camera(t_cam *cam);
void	init_light(t_light *light);
int		parse_ambience(t_scene *scene);
int		parse_camera(t_scene *scene);
int		parse_light(t_scene *scene);
void	errors_file(int error_code);
void	errors_parsing(t_pars *pars);

// FREE
void	free_parsing_and_exit(t_pars *parsing);
int		ft_freearray(char **arr);

// UTILS
int		array_length(char **array);
int		only_numbers_and_newline(char *str);
int		only_numbers_dec_pt_and_newline(char *str);
int		only_numbers_single_signs_and_dec_pt(char *str);
int		ft_strchr_index(char *str, char c);

#endif
