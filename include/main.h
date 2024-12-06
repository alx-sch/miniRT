/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/06 15:36:54 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The primary inclusion point for the project, including all necessary libraries
and declaring all function prototypes.
*/

#ifndef MAIN_H
# define MAIN_H

// Standard C libraries
# include <unistd.h>		// for open(), close(), read(), write()
# include <stdio.h>			// for printf(), perror()
# include <string.h>		// for strerror()
# include <stdlib.h>		// for malloc(), free(), exit()
# include <errno.h>			// for errno
# include <math.h>			// for math functions, expr, e.g. sqrt(), INFINITY
# include <fcntl.h>			// for open() macros

// X11 library headers
# include <X11/keysym.h>	// Macros for key symbols, e.g. XK_Escape
# include <X11/X.h>			// Macros for event names, e.g. DestroyNotify

// Custom headers
# include "libft.h"			// libft
# include "mlx.h"			  // mlx
# include "errors.h"		// Error messages and formatting styles
# include "types.h"			// Typedefs, data structs, e.g. 't_rt'
# include "parsing.h"		// Parsing header file
# include "colors.h"		// TEST ONLY NOT NEEDED IN FINAL PROJECT

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

void	start_event_loop(t_rt *rt);

// ray.c

int		ray_intersect_plane(t_vec3 ray_dir, t_plane *plane, double *t);
int		ray_intersect_sphere(t_vec3 ray_dir, t_sphere *sphere, double *t);
int		ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir,
			t_cylinder *cylinder, double *t);

int		ray_intersect_cap_top(t_vec3 ray_origin, t_vec3 ray_dir,
			t_cylinder *cylinder, double *t);
int		ray_intersect_cap_bottom(t_vec3 ray_origin, t_vec3 ray_dir,
			t_cylinder *cylinder, double *t);

void	render_scene(t_rt *rt, int bg_color);

// utils/0_vector_utils.c

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mult(t_vec3 v, double scalar);
double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_norm(t_vec3 v);

// utils/1_quadratic_utils.c

double	calculate_discriminant(double a, double b, double c);
double	calculate_entry_distance(double a, double b, double discriminant);
double	calculate_exit_distance(double a, double b, double discriminant);

// utils/2_pixel_utils.c

int		color_to_hex(t_color color);
void	set_pixel_color(t_img *img, int x, int y, int color);

// utils/3_cleanup.c

void	cleanup(t_rt **rt_ptr);

// utils/4_error_exit.c

void	cleanup_error_exit(char *msg, t_rt *rt);

/*
	PARSING
*/


// GENERAL --FREE

void	free_parsing(t_pars *parsing);
int		ft_freearray(char **arr);
void	free_scene_and_exit(t_scene *scene, t_rt *rt);
void	free_scene(t_scene *scene);

// GENERAL -- UTILS

int		array_length(char **array);
double	ft_atod(char *str);
int		ft_strchr_index(char *str, char c);
int		only_numbers_and_newline(char *str);
int		only_numbers_dec_pt_and_newline(char *str);
int		only_numbers_single_signs_and_dec_pt(char *str);
int		only_numbers_and_dec_pt(char *str);
char	**ft_split_by_spaces(const char *s);

#endif
