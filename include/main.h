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

// To avoid including headers solely for macros (norminette):
// <X11/keysym.h> and <X11/X.h>
# define XK_ESCAPE		0xff1b	// Key code for the 'Esc' key
# define DESTROY_NOTIFY	17		// Event code for window destruction

# define BG_COLOR		0x303030	// Anthracite (dark grey)
# define EPSILON 		1e-3	// Small value to avoid floating-point errors
# define K_DIFFUSE		0.7		// Diffuse intensity factor [0.0, 1.0]
# define K_SPECULAR		0.7		// Specular intensity factor [0.0, 1.0]

# define SPECULAR		0		// Display specular highlights (1) or not (0)
// Shininess factor for specular highlighting.
// Controls of how glossy the specular highlight is (the bigger the value, the
// smaller / more focused the highlight).
// [0.0, INT_MAX], but values between 3.0 and 10.0 are recommended.
# define K_SHININESS	5.0

# define FADE			0		// Display light fade (1) or not (0)
// Fade factor for light intensity.
// Controls the rate at which light intensity diminishes as the distance
// increases (the bigger the value, the farther the light reaches).
// [0.0, INT_MAX], but values between 3.0 and 10.0 are recommended.
# define K_FADE			7.0

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

// 6_pixel_shading.c

t_shade	get_shading(t_rt *rt, t_ix *ix);

// 7_render_scene.c

void	render_scene(t_rt *rt);

//####################
//# UTILS PROTOTYPES #
//####################

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

// utils/2_color_utils.c

int		color_to_hex(t_color color);
void	set_pixel_color(t_img *img, int x, int y, int color);
double	clamp(double value, double max);

// utils/3_cleanup.c

void	cleanup(t_rt **rt_ptr);

// utils/4_error_exit.c

void	cleanup_error_exit(char *msg, t_rt *rt);

#endif
