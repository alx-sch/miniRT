/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:58:53 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/10 13:25:14 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Welcome to the parsing header file!

	When ./miniRT is ran, it expects an argument <scene.rt>. This file needs
	to comply to certain rules.
	The parsing part of the program takes care of the following:
	1. The file is of type ".rt".
	2. The file exists/can be accessed.
	3. The unique elements - like 'A', 'C' and 'L' only occure once in the file.
	4. Checks that all the type identifiers exist.
	5. Checks that the necessary identifiers (ambience, camera and light) are
	all present.
	6. Every single element aligns with the expected requirements.
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

	The main structure of the parsing is as follows:
	1. Checks file related errors -- like file permissions, existence etc.
	2. Reads the file line by line, and splits each line into several fields
	using ft_split_by_spaces.
	3. Parses each single line, and if everything is valid, it stores all
	values.
		--> For unique elements, there are designated spots in the t_scene
		struct.
		--> For nonunique elements, an object node is added to the linked list
		of t_scene struct, which will ultimately contain all the objects.
	4. If there are no errors after parsing is done - the t_scene will be
	populated with all the data from the rt-file.
*/

#ifndef PARSING_H
# define PARSING_H

# include "types.h" // for type definitions

// Forward declarations
typedef struct s_rt				t_rt;
typedef struct s_scene			t_scene;
typedef struct s_ambi_light		t_ambi_light;
typedef struct s_camera			t_cam;
typedef struct s_light			t_light;
typedef union u_object_data		t_obj_data;

/*
	ERROR CODES -- PARSING
*/
enum e_pars_errors
{
	ERR_USAGE = 1,
	ERR_FILE_EXTENSION = 2,
	ERR_FILE_ACCESS = 3,
	ERR_MEM_ALLOC = 4,
	ERR_UNIQUE_ELEM = 5,
	ERR_INVALID_IDENTIFIER = 6,
	ERR_FILE_EMPTY = 7,
	ERR_MISSING_IDENTIFIER = 8,
	ERR_AMB_FIELDS = 9,
	ERR_AMB_LIGHT = 10,
	ERR_AMB_COLOR_FIELDS = 11,
	ERR_AMB_COLOR_VALUES = 12,
	ERR_CAM_FIELDS = 13,
	ERR_CAM_COOR_FIELDS = 14,
	ERR_CAM_COOR_VALUES = 15,
	ERR_CAM_VECTOR_FIELDS = 16,
	ERR_CAM_VECTOR_VALUES = 17,
	ERR_CAM_VECTOR_NORM = 18,
	ERR_CAM_FIELD_OF_VIEW = 19,
	ERR_LIGHT_FIELDS = 20,
	ERR_LIGHT_COOR_FIELDS = 21,
	ERR_LIGHT_COOR_VALUES = 22,
	ERR_LIGHT_BRIGHTNESS = 23,
	ERR_LIGHT_COLOR_FIELDS = 24,
	ERR_LIGHT_COLOR_VALUES = 25,
	ERR_SP_FIELDS = 26,
	ERR_SP_COOR_FIELDS = 27,
	ERR_SP_COOR_VALUES = 28,
	ERR_SP_DM = 29,
	ERR_SP_COLOR_FIELDS = 30,
	ERR_SP_COLOR_VALUES = 31,
	ERR_PL_FIELDS = 32,
	ERR_PL_COOR_FIELDS = 33,
	ERR_PL_COOR_VALUES = 34,
	ERR_PL_VECTOR_FIELDS = 35,
	ERR_PL_VECTOR_VALUES = 36,
	ERR_PL_VECTOR_NORM = 37,
	ERR_PL_COLOR_FIELDS = 38,
	ERR_PL_COLOR_VALUES = 39,
	ERR_CY_FIELDS = 40,
	ERR_CY_COOR_FIELDS = 41,
	ERR_CY_COOR_VALUES = 42,
	ERR_CY_VECTOR_FIELDS = 43,
	ERR_CY_VECTOR_VALUES = 44,
	ERR_CY_VECTOR_NORM = 45,
	ERR_CY_DM = 46,
	ERR_CY_HEIGHT = 47,
	ERR_CY_COLOR_FIELDS = 48,
	ERR_CY_COLOR_VALUES = 49
};

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
# define ERR_MSG_CAM_VECTOR_NORM "Error\nCamera orientation vector is not \
normalized.\n"
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
# define ERR_MSG_PL_VECTOR_NORM "Error\nPlane orientation vector is not \
normalized.\n"
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
# define ERR_MSG_CY_VECTOR_NORM "Error\nCylinder orientation vector is not \
normalized.\n"
# define ERR_MSG_CY_DM "Error\nCylinder diameter must be within the range of a \
double.\n"
# define ERR_MSG_CY_HEIGHT "Error\nCylinder height must be within the range \
of a double.\n"
# define ERR_MSG_CY_COLOR_FIELDS "Error\nNeed 3 cylinder color values.\n"
# define ERR_MSG_CY_COLOR_VALUES "Error\nCylinder color values must be between \
0 and 255.\n"

/*
	STRUCTURES -- PARSING
*/

/*
Structure representing the parts needed for parsing.
- int 'a_found', 'c_found' and 'l_found':
Ambient light, camera and light are all unique objects, so these variables
indicate if they occure more than once.
- int 'fd':				Used to store the file descriptor of the .rt-file.
- int 'error_code':		Used to store the error code indicating the issue.
- char *element:		Used to store a line from the rt-file, using gnl.
- char **elem_data:		Used to store a line from the rt-file, separated by
spaces.
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
}	t_pars;

/*
	FUNCTIONS -- PARSING
*/

// 0_parsing/parsing.c
void		parse_and_set_objects(t_rt *rt, int argc, char **argv);

// 0_parsing/errors/errors_elements.c
void		sphere_errors(t_pars *parsing, int count);
void		plane_errors(t_pars *parsing, int count);
void		cylinder_errors(t_pars *parsing, int count);

// 0_parsing/errors/errors_unique_elements.c
void		ambience_errors(t_pars *parsing);
void		camera_errors(t_pars *parsing);
void		light_errors(t_pars *parsing);

// 0_parsing/errors/errors.c
void		errors_file(int error_code, t_rt *rt);
void		errors_parsing(t_rt *rt, t_scene *scene, t_pars *pars);

// 0_parsing/errors/set_error_and_return.c
int			set_error_and_return(char **arr, int **parsing_error, \
int error_code);

// 0_parsing/free/free_array.c
int			ft_freearray(char **arr);

// 0_parsing/free/free_parsing.c
void		free_parsing(t_pars *parsing);

// 0_parsing/free/free_scene.c
void		free_scene_and_exit(t_scene *scene, t_rt *rt);
void		free_scene(t_scene *scene);

// 0_parsing/init/init_scene.c
void		init_parsing(t_pars *parsing);
void		init_scene(t_scene *scene);

// 0_parsing/init/init_unique_elements.c
void		init_ambience(t_ambi_light *amb);
void		init_camera(t_cam *cam);
void		init_light(t_light *light);

// 0_parsing/parse_and_set/check_data/check_color.c
int			check_color(char **rgb, int *parsing_error, int error_code);

// 0_parsing/parse_and_set/check_data/check_coordinates.c
int			check_coordinates(char *input_coords, int *parsing_error, \
int error_code);

// 0_parsing/parse_and_set/check_data/check_file.c
int			check_file_existence(char *str);
int			check_file_extension(char *str);

// 0_parsing/parse_and_set/check_data/check_identifiers.c
int			all_necessary_identifiers(t_pars *pars);
int			check_unique_identifier(t_pars *parsing, char *str);

// 0_parsing/parse_and_set/check_data/check_orientation_vector.c
int			check_orientation_vector(char *input_coords, int *parsing_error, \
int error_code);

// 0_parsing/parse_and_set/check_data/correct_amt_of_fields.c
int			correct_amt_of_fields(char **arr, int expected_len);

// 0_parsing/parse_and_set/elements/add_to_object_list.c
int			add_to_object_list(t_scene **scene, t_obj_data **obj_data);

// 0_parsing/parse_and_set/elements/check_and_set_single_element.c
int			check_and_set_single_element(t_scene *scene);

// 0_parsing/parse_and_set/elements/check_and_set (Directory)
int			parse_and_set_ambience(t_scene *scene);
int			parse_and_set_camera(t_scene *scene);
int			parse_and_set_light(t_scene *scene);
int			parse_sphere(t_scene *scene);
int			parse_plane(t_scene *scene);
int			parse_cylinder(t_scene *scene);

// 0_parsing/parse_and_set/set_data (Directory)
int			set_coordinates(char *input_coords, double *x, double *y, \
double *z);
int			set_orientation_vector(char *input_coords, double *x, double *y, \
double *z);
void		set_color(char **rgb, unsigned char *r, unsigned char *g, \
unsigned char *b);

// 0_parsing/utils/array_length.c
int			array_length(char **array);

// 0_parsing/utils/ft_atod.c
double		ft_atod(char *str);

// 0_parsing/utils/ft_split_by_spaces.c
char		**ft_split_by_spaces(const char *s);

// 0_parsing/utils/ft_strchr_index.c
int			ft_strchr_index(char *str, char c);

// 0_parsing/utils/only_numbers.c
int			only_numbers_and_newline(char *str);
int			only_numbers_dec_pt_and_newline(char *str);
int			only_numbers_single_signs_and_dec_pt(char *str);
int			only_numbers_and_dec_pt(char *str);

#endif
