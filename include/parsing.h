/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:58:53 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:28:39 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*
	Welcome to the parsing header file!
	
	When ./miniRT is ran, it expects an argument <scene.rt>. This file needs
	to comply to certain rules.
	The parsing part of the program takes care of the following:
	1. The file is of type ".rt".
	2. The file exists/can be accessed.
	3. The unique elements - like 'A', 'C' and 'L' only occure once in the file.
	4. Checks that the type identifier exists.
	5. Every single element aligns with the expected requirements.
	These are as following:

		Ambient lightning:
			A 0.2 255,255,255
			∗ identifier: A
			∗ ambient lighting ratio in range [0.0,1.0]: 0.2
			∗ R,G,B colors in range [0-255]: 255, 255, 255
		Camera:
			C -50.0,0,20 0,0,1 70
			∗ identifier: C
			∗ x,y,z coordinates of the view point: -50.0,0,20
			∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
			0.0,0.0,1.0
			∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
		Light:
			L -40.0,50.0,0.0 0.6 10,0,255
			∗ identifier: L
			∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
			∗ the light brightness ratio in range [0.0,1.0]: 0.6
			∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
		Cylinder:
			cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
			∗ identifier: cy
			∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
			∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each
			x,y,z axis: 0.0,0.0,1.0
			∗ the cylinder diameter: 14.2
			∗ the cylinder height: 21.42
			∗ R,G,B colors in range [0,255]: 10, 0, 255
		Plane:
			pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
			∗ identifier: pl
			∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
			∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 
			0.0,1.0,0.0
			∗ R,G,B colors in range [0-255]: 0,0,225
		Sphere:
			sp 0.0,0.0,20.6 12.6 10,0,255
			∗ identifier: sp
			∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
			∗ the sphere diameter: 12.6
			∗ R,G,B colors in range [0-255]: 10, 0, 255
		
	The program will show a descriptive error message and exit with an error code,
	depending on what the issue was.
*/

/*
	ERROR CODES -- PARSING
*/
typedef enum e_pars_errors
{
	ERR_USAGE = 1,
	ERR_FILE_EXTENSION,
	ERR_FILE_ACCESS,
	ERR_MEM_ALLOC,
	ERR_UNIQUE_ELEM,
	ERR_INVALID_IDENTIFIER,
	ERR_FILE_EMPTY,
	ERR_MISSING_IDENTIFIER,
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
	ERR_SP_FIELDS,
	ERR_SP_COOR_FIELDS,
	ERR_SP_COOR_VALUES,
	ERR_SP_DM,
	ERR_SP_COLOR_FIELDS,
	ERR_SP_COLOR_VALUES,
	ERR_PL_FIELDS,
	ERR_PL_COOR_FIELDS,
	ERR_PL_COOR_VALUES,
	ERR_PL_VECTOR_FIELDS,
	ERR_PL_VECTOR_VALUES,
	ERR_PL_COLOR_FIELDS,
	ERR_PL_COLOR_VALUES,
	ERR_CY_FIELDS,
	ERR_CY_COOR_FIELDS,
	ERR_CY_COOR_VALUES,
	ERR_CY_VECTOR_FIELDS,
	ERR_CY_VECTOR_VALUES,
	ERR_CY_DM,
	ERR_CY_HEIGHT,
	ERR_CY_COLOR_FIELDS,
	ERR_CY_COLOR_VALUES
}	t_pars_errors;

/*
	ERROR MESSAGES -- PARSING
*/
# define ERR_MSG_USAGE "Error\nUsage: ./miniRT <scene.rt>\n"
# define ERR_MSG_FILE_EXTENSION "Error\nFile extension must be of type '.rt'.\n"
# define ERR_MSG_FILE_ACCESS "Error\nCan't access scene description file"
# define ERR_MSG_MEM_ALLOC "Error\nMemory allocation failure.\n"
# define ERR_MSG_UNIQUE_ELEM "Error\nAmbience, camera and light source can only\
 occure once. It must be written as a single 'A', 'C' or 'L'.\n"
# define ERR_MSG_INVALID_IDENTIFIER "Error\nInvalid identifier found. \
The following are allowed:\n[A] Ambience\n[C] Camera\n[L] Light\n[sp] Sphere\n\
[pl] Plane\n[cy] Cylinder\n"
# define ERR_MSG_FILE_EMPTY "Error\n.rt-file can't be empty.\n"
# define ERR_MSG_MISSING_IDENTIFIER "Error\nMissing either ambience, camera or \
light. Must be ONE of each.\n"
# define ERR_MSG_AMB_FIELDS "Error\nAmbient light must have 3 fields.\n"
# define ERR_MSG_AMB_LIGHT "Error\nAmbient light must be between 0.0 and 1.0.\n"
# define ERR_MSG_AMB_COLOR_FIELDS "Error\nNeed 3 ambient color values.\n"
# define ERR_MSG_AMB_COLOR_VALUES "Error\nAmbient color values must be between \
0 and 255.\n"
# define ERR_MSG_CAM_FIELDS "Error\nCamera must have 4 fields.\n"
# define ERR_MSG_CAM_COOR_FIELDS "Error\nNeed 3 camera coordinate values.\n"
# define ERR_MSG_CAM_COOR_VALUES "Error\nCamera coordinates must be within the \
range of a double.\n"
# define ERR_MSG_CAM_VECTOR_FIELDS "Error\nNeed 3 camera orientation vector \
values.\n"
# define ERR_MSG_CAM_VECTOR_VALUES "Error\nCamera orientation vector values \
must be between -1 and 1.\n"
# define ERR_MSG_CAM_FIELD_OF_VIEW "Error\nCamera's horizontal field of view \
must be a number between 0 and 180.\n"
# define ERR_MSG_LIGHT_FIELDS "Error\nLight field must have 3 or 4 fields.\n"
# define ERR_MSG_LIGHT_COOR_FIELDS "Error\nNeed 3 light coordinate values.\n"
# define ERR_MSG_LIGHT_COOR_VALUES "Error\nLight coordinates must be within \
the range of a double\n"
# define ERR_MSG_LIGHT_BRIGHTNESS "Error\nLight brightness must be between 0 \
and 1.\n"
# define ERR_MSG_LIGHT_COLOR_FIELDS "Error\nNeed 3 light color values.\n"
# define ERR_MSG_LIGHT_COLOR_VALUES "Error\nLight color values must be between \
0 and 255.\n"
# define ERR_MSG_SP_FIELDS "Error\nSphere must have 4 fields.\n"
# define ERR_MSG_SP_COOR_FIELDS "Error\nNeed 3 sphere coordinate values.\n"
# define ERR_MSG_SP_COOR_VALUES "Error\nSphere coordinates must be within the \
range of a double.\n"
# define ERR_MSG_SP_DM "Error\nSphere diameter must be within the range of a \
double.\n"
# define ERR_MSG_SP_COLOR_FIELDS "Error\nNeed 3 sphere color values.\n"
# define ERR_MSG_SP_COLOR_VALUES "Error\nSphere color values must be between \
0 and 255.\n"
# define ERR_MSG_PL_FIELDS "Error\nPlane must have 4 fields.\n"
# define ERR_MSG_PL_COOR_FIELDS "Error\nNeed 3 plane coordinate values.\n"
# define ERR_MSG_PL_COOR_VALUES "Error\nPlane coordinates must be within the \
range of a double.\n"
# define ERR_MSG_PL_VECTOR_FIELDS "Error\nNeed 3 plane orientation vector \
values.\n"
# define ERR_MSG_PL_VECTOR_VALUES "Error\nPlane orientation vector values \
must be between -1 and 1.\n"
# define ERR_MSG_PL_COLOR_FIELDS "Error\nNeed 3 plane color values.\n"
# define ERR_MSG_PL_COLOR_VALUES "Error\nPlane color values must be between \
0 and 255.\n"
# define ERR_MSG_CY_FIELDS "Error\nCylinder must have 6 fields.\n"
# define ERR_MSG_CY_COOR_FIELDS "Error\nNeed 3 cylinder coordinate values.\n"
# define ERR_MSG_CY_COOR_VALUES "Error\nSphere coordinates must be within the \
range of a double.\n"
# define ERR_MSG_CY_VECTOR_FIELDS "Error\nNeed 3 cylinder orientation vector \
values.\n"
# define ERR_MSG_CY_VECTOR_VALUES "Error\nCylinder orientation vector values \
must be between -1 and 1.\n"
# define ERR_MSG_CY_DM "Error\nCylinder diameter must be within the range of a \
double.\n"
# define ERR_MSG_CY_HEIGHT "Error\nCylinder height must be within the range \
of a double.\n"
# define ERR_MSG_CY_COLOR_FIELDS "Error\nNeed 3 cylinder color values.\n"
# define ERR_MSG_CY_COLOR_VALUES "Error\nCylinder color values must be between \
0 and 255.\n"

/*
	STRUCTS -- PARSING
*/

typedef struct s_pars
{
	int		a_found;
	int		c_found;
	int		l_found;
	int		fd;
	int		error_code;
	char	*element;
	char	**elem_data;
	int		sp_count;
	int		cy_count;
	int		pl_count;
}	t_pars;

typedef struct s_ambience
{
	double			light;
	unsigned char	color_r;
	unsigned char	color_g;
	unsigned char	color_b;
}	t_amb;

typedef struct s_camera
{
	double			x;
	double			y;
	double			z;
	double			vec_x;
	double			vec_y;
	double			vec_z;
	unsigned char	field;
}	t_cam;

typedef struct s_light
{
	double			x;
	double			y;
	double			z;
	double			bright;
	unsigned char	color_r;
	unsigned char	color_g;
	unsigned char	color_b;
}	t_light;

typedef struct s_sp
{
	double			x;
	double			y;
	double			z;
	double			dm;
	unsigned char	color_r;
	unsigned char	color_g;
	unsigned char	color_b;
}	t_sp;

typedef struct s_pl
{
	double			x;
	double			y;
	double			z;
	double			vec_x;
	double			vec_y;
	double			vec_z;
	unsigned char	color_r;
	unsigned char	color_g;
	unsigned char	color_b;
}	t_pl;

typedef struct s_cy
{
	double			x;
	double			y;
	double			z;
	double			vec_x;
	double			vec_y;
	double			vec_z;
	double			dm;
	double			height;
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
	t_sp			*sp;
	t_pl			*pl;
	t_cy			*cy;
	int				tot_sp;
	int				tot_cy;
	int				tot_pl;
}	t_scene;

/*
	FUNCTIONS -- PARSING
*/

t_scene	parse_and_set_objects(int argc, char **argv);

// PARSING -- ERRORS
void	errors_file(int error_code);
void	errors_parsing(t_scene *scene, t_pars *pars);
void	ambience_errors(t_pars *parsing);
void	camera_errors(t_pars *parsing);
void	light_errors(t_pars *parsing);
void	sphere_errors(t_pars *parsing, int count);
void	plane_errors(t_pars *parsing, int count);
void	cylinder_errors(t_pars *parsing, int count);
int		set_error_and_return(char **arr, int *parsing_error, int error_code);

// PARSING -- INITS
void	init_parsing(t_pars *parsing);
void	init_scene(t_scene *scene);
void	init_ambience(t_amb *amb);
void	init_camera(t_cam *cam);
void	init_light(t_light *light);
void	init_sphere(t_sp *sp);
void	init_plane(t_pl *pl);
void	init_cylinder(t_cy *cy);
int		allocate_nonunique_elements(t_scene *scene);

// PARSING -- PARSE EACH ELEMENT
int		correct_amt_of_fields(char **arr, int expected_len);
int		parse_and_set_ambience(t_scene *scene);
int		parse_and_set_camera(t_scene *scene);
int		parse_and_set_light(t_scene *scene);
int		parse_sphere(t_scene *scene);
int		parse_plane(t_scene *scene);
int		parse_cylinder(t_scene *scene);
int		check_coordinates(char *input_coords, int *parsing_error, \
int error_code);
int		check_orientation_vector(char *input_coords, int *parsing_error, \
int error_code);
int		check_color(char **rgb, int *parsing_error, int error_code);

// PARSING -- SET EACH ELEMENT
int		set_cylinder(t_scene *scene, t_cy *cy);
int		set_plane(t_scene *scene, t_pl *pl);
int		set_sphere(t_scene *scene, t_sp *sp);
int		set_coordinates(char *input_coords, double *x, double *y, double *z);
int		set_orientation_vector(char *input_coords, double *x, double *y, \
double *z);
void	set_color(char **rgb, unsigned char *r, unsigned char *g, \
unsigned char *b);

// PARSING -- PARSE FILE
int		all_necessary_identifiers(t_pars *pars);
int		check_file_existence(char *str);
int		check_file_extension(char *str);
int		check_unique_identifier(t_pars *parsing, char *str);
int		check_single_element(t_scene *scene);
int		set_single_element(t_scene *scene);

#endif
