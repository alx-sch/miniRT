/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:07 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/19 17:41:11 by aschenk          ###   ########.fr       */
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
# include "mlx.h"			// mlx
# include "errors.h"		// Error messages and formatting styles
# include "types.h"			// Typedefs, data structs, e.g. 't_rt'
# include "parsing.h"		// Parsing header file

//#############
//# CONSTANTS #
//#############

# define WINDOW_TITLE	"miniRT by Natalie Holbrook & Alex Schenk @42Berlin"
# define BG_COLOR		0x303030  // Anthracite (dark grey)
# define EPSILON 		1e-3

//##################
//# FCT PROTOTYPES #
//##################

// main.c

int		main(int argc, char **argv);

// 1_mlx_initialization.c

void	init_mlx(t_rt *rt);

// 2_event_handling.c

void	start_event_loop(t_rt *rt);

// 3_ray_hit_plane.c

int		ray_hit_plane(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t);

// 3_ray_hit_sphere.c

int		ray_hit_sphere(t_vec3 ray_ori, t_vec3 ray_dir, t_obj *obj, double *t);

// 3_ray_hit_cylinder.c

int		ray_hit_cyl(t_vec3 ray_origin, t_vec3 ray_dir, t_obj *obj, double *t);
int		ray_hit_cap_top(t_vec3 ray_origin, t_vec3 ray_dir, t_obj *obj,
			double *t);
int		ray_hit_cap_bottom(t_vec3 ray_origin, t_vec3 ray_dir, t_obj *obj,
			double *t);

// 4_find_intersection.c

void	find_ix(t_vec3 ray_ori, t_vec3 ray_dir, t_rt *rt, t_ix *ixr);

// 5_compute_rays.c

t_vec3	compute_camera_ray(int x, int y, t_cam cam);
t_shdw	compute_shadow_ray(t_ix *camera_ray_ix, t_light light);

// 5_ray_render.c

void	render_scene(t_rt *rt);

// 6_compute_color.c
void	compute_color(t_vec3 ray_dir, t_rt *rt, t_ix *ix);

// 7_shadow_intersections.c

// int			shadow_check_plane_intersection(t_rt *rt, t_vec3 ray_dir,
// 				t_plane pl, t_ix **ixr);
// int			shadow_check_sphere_intersection(t_rt *rt, t_vec3 ray_dir,
// 				t_sphere sp, t_ix **ixr);
// int			shadow_check_cyl_intersection(t_rt *rt, t_vec3 ray_dir,
// 				t_cylinder cy, t_ix **ixr);
// int			is_ray_in_shadow(t_rt *rt, t_ix *ixr);

// // 8_create_shadow_ray.c

// t_shadow	init_shadow(t_rt *rt, t_ix *ixr, t_vec3 ray_dir);
// t_vec3		get_normal_at_point(t_vec3 point, t_obj *obj);
// t_vec3		calculate_cylinder_normal(t_vec3 intersection_point,
// 				t_obj *obj);

// // 9_shadow_copy_objs.c

// t_cylinder	copy_cylinder(t_cylinder *cyl, t_shadow *shadow);
// t_sphere	copy_sphere(t_sphere *sp, t_shadow *shadow);
// t_plane		copy_plane(t_plane *pl, t_shadow *shadow);

// utils/0_vector_utils_1.c

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mult(t_vec3 vec, double scalar);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);
double	vec3_dot(t_vec3 v1, t_vec3 v2);

// utils/0_vector_utils_2.c

t_vec3	vec3_new(double x, double y, double z);
t_vec3	vec3_norm(t_vec3 vec);
t_vec3	vec3_scale(t_vec3 v, double scalar);
double	vec3_length(t_vec3 v);

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

#endif
