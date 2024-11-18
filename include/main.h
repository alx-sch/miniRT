/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/18 18:46:58 by nholbroo         ###   ########.fr       */
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

// CUSTOM ERROR MESSAGES
# define ERR_MSG_USAGE "Error\nUsage: ./miniRT <scene.rt>\n"
# define ERR_MSG_FILE_EXTENSION "Error\nFile extension must be of type '.rt'.\n"
# define ERR_MSG_FILE_ACCESS "Error\nCan't access scene description file"
# define ERR_MSG_MEM_ALLOC "Error\nMemory allocation failure.\n"
# define ERR_MSG_UNIQUE_ELEM "Error\nAmbience, camera and light source can only\
 occure once. It must be written as a single 'A', 'C' or 'L'.\n"
# define ERR_MSG_FILE_EMPTY "Error\n.rt-file can't be empty.\n"
# define ERR_MSG_AMB_FIELDS "Error\nAmbient light must have 3 fields.\n"
# define ERR_MSG_AMB_LIGHT "Error\nAmbient light must be between 0.0 and 1.0.\n"
# define ERR_MSG_AMB_COLOR_FIELDS "Error\nNeed 3 ambient color values.\n"
# define ERR_MSG_AMB_COLOR_VALUES "Error\nAmbient color values must be between \
0 and 255.\n"
# define ERR_MSG_CAM_FIELDS "Error\nCamera must have 4 fields.\n"
# define ERR_MSG_CAM_COOR_FIELDS "Error\nNeed 3 camera coordinate values.\n"
# define ERR_MSG_CAM_COOR_VALUES "Error\nCamera coordinates must be within the \
range of a float.\n"
# define ERR_MSG_CAM_VECTOR_FIELDS "Error\nNeed 3 camera orientation vector \
values.\n"
# define ERR_MSG_CAM_VECTOR_VALUES "Error\nCamera orientation vector values \
must be between -1 and 1.\n"
# define ERR_MSG_CAM_FIELD_OF_VIEW "Error\nCamera's horizontal field of view \
must be a number between 0 and 180.\n"
# define ERR_MSG_LIGHT_FIELDS "Error\nLight field must have 4 fields.\n"
# define ERR_MSG_LIGHT_COOR_FIELDS "Error\nNeed 3 light coordinate values.\n"
# define ERR_MSG_LIGHT_COOR_VALUES "Error\nLight coordinates must be within \
the range of a float\n"
# define ERR_MSG_LIGHT_BRIGHTNESS "Error\nLight brightness must be between 0 \
and 1.\n"
# define ERR_MSG_LIGHT_COLOR_FIELDS "Error\nNeed 3 light color values.\n"
# define ERR_MSG_LIGHT_COLOR_VALUES "Error\nLight color values must be between \
0 and 255.\n"

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

typedef struct s_sp
{
	float			x;
	float			y;
	float			z;
	float			dm;
	unsigned char	color_r;
	unsigned char	color_g;
	unsigned char	color_b;
}	t_sp;

typedef struct s_pl
{
	float			x;
	float			y;
	float			z;
	float			vec_x;
	float			vec_y;
	float			vec_z;
	unsigned char	color_r;
	unsigned char	color_g;
	unsigned char	color_b;
}	t_pl;

typedef struct s_cy
{
	float			x;
	float			y;
	float			z;
	float			vec_x;
	float			vec_y;
	float			vec_z;
	float			dm;
	float			height;
	unsigned char	color_r;
	unsigned char	color_g;
	unsigned char	color_b;
}	t_cy;

typedef struct s_scene
{
	t_pars			pars;
	t_amb			amb;
	t_cam			cam;
	t_light			light;
	t_sp			sp;
	t_pl			pl;
	t_cy			cy;
}	t_scene;

typedef enum e_pars_errors
{
	ERR_USAGE = 1,
	ERR_FILE_EXTENSION,
	ERR_FILE_ACCESS,
	ERR_MEM_ALLOC,
	ERR_UNIQUE_ELEM,
	ERR_FILE_EMPTY,
	ERR_AMB_FIELDS,
	ERR_AMB_LIGHT,
	ERR_AMB_COLOR_FIELDS,
	ERR_AMB_COLOR_VALUES,
	ERR_CAM_FIELDS,
	ERR_CAM_COOR_FIELDS,
	ERR_CAM_COOR_VALUES,
	ERR_CAM_VECTOR_FIELDS,
	ERR_CAM_VECTOR_VALUES,
	ERR_CAM_FIELD_OF_VIEW,
	ERR_LIGHT_FIELDS,
	ERR_LIGHT_COOR_FIELDS,
	ERR_LIGHT_COOR_VALUES,
	ERR_LIGHT_BRIGHTNESS,
	ERR_LIGHT_COLOR_FIELDS,
	ERR_LIGHT_COLOR_VALUES,
}	t_pars_errors;

/*PARSING*/
float	ft_atof(char *str);
t_scene	parsing(int argc, char **argv);
int		check_file_existence(char *str);
int		check_file_extension(char *str);
int		parse_ambience(t_scene *scene);
int		parse_camera(t_scene *scene);
int		parse_light(t_scene *scene);

// PARSING -- INITS
void	init_parsing(t_pars *parsing);
void	init_scene(t_scene *scene);
void	init_ambience(t_amb *amb);
void	init_camera(t_cam *cam);
void	init_light(t_light *light);
void	init_sphere(t_sp *sp);
void	init_plane(t_pl *pl);
void	init_cylinder(t_cy *cy);

// PARSING -- ERRORS
void	errors_file(int error_code);
void	errors_parsing(t_pars *pars);
void	ambience_errors(t_pars *parsing);
void	camera_errors(t_pars *parsing);
void	light_errors(t_pars *parsing);

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
