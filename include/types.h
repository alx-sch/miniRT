/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:55:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/29 10:43:17 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Defines the types and data structures used in the raytracer program.
*/

#ifndef TYPES_H
# define TYPES_H

# include "libft.h"	// for 't_list' definition

//#######
//# MLX #
//#######

/*
Data structure holding image info, incl. dimensions, pixel data, color, and
endianess.
- void *`img_prt`:	Pointer to image object. Used when manipulating image as a
					whole, e.g. loading into memory or passing to redering ftcs.
- int *`data_ptr`:	Pointer to the start of image data -> raw pixel information.
					Used in operations reading/modifying individual pixels, such
					as setting the color. int values represent whole pixels.
- int `bits_per_pixel`:	Number of bits used to represent each pixel,
						holds the color.
- int `line_size`:	Length of each line in the image in bytes,
					indicating the number of bytes needed to store a single
					row of pixels in the image.
- int `endian`:		Endianness refers to the byte order in which data types are
					stored in memory (either big or little endian; left to right
					and right to left, respectively). Used to determine how to
					interpret image data ('img' and 'data' members).
*/
typedef struct s_img
{
	void	*img_ptr;
	int		*data_ptr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img;

/*
Data structure holding MiniLibX components for rendering the raytracer output.
- void *`mlx`:		Pointer to the MiniLibX context.
- void *`win`:		Pointer to the window object.
- t_img `img`:		Image structure containing pixel data, color, and endianess.
*/
typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_mlx;

//#################
//# UTILS STRCUTS #
//#################

/**
Structure representing a 3D vector or a point.
- double `x`:		The x-coordinate/-component of the vector.
- double `y`:		The y-coordinate/-component of the vector.
- double `z`:		The z-coordinate/-component of the vector.
*/
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/**
Structure representing a color in RGB format:
- int `r`: The red component of the color [0-255].
- int `g`: The green component of the color [0-255].
- int `b`: The blue component of the color [0-255].
*/
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

//###########
//# OBJECTS #
//###########

/**
Enumeration representing different types of 3D objects.
*/
typedef enum e_object_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_obj_type;

/**
Structure representing a plane in 3D space:
 - t_object `object_type`:	The object type (always `PLANE`).
 - t_vec3 `point_in_plane`:	A point that lies on the plane.
 - t_vec3 `normal`:			A normalized vector representing the plane's normal,
							which is perpendicular to the plane's surface.
 - t_color `color`:			The color of the plane.
 */
typedef struct s_plane
{
	t_obj_type	object_type;
	t_vec3		point_in_plane;
	t_vec3		normal;
	t_color		color;
}	t_plane;

/**
Structure representing a sphere in 3D space.
 - t_object `object_type`:	The object type (always `SPHERE`).
 - t_vec3 `center`:			The center point of the sphere.
 - double `radius`:			The radius of the sphere.
 - t_color `color`:			The color of the sphere.
*/
typedef struct s_sphere
{
	t_obj_type	object_type;
	t_vec3		center;
	double		radius;
	t_color		color;
}	t_sphere;

/**
Structure representing a cylinder in 3D space:
 - t_object `object_type`:	The object type (always `CYLINDER`).
 - t_vec3 `center`:			The center of the cylinder's base.
 - t_vec3 `orientation`:	A normalized vector representing the cylinder's axis.
 - double `radius`:			The radius of the cylinder.
 - double `height`:			The height of the cylinder.
 - t_color `color`:			The color of the cylinder.
*/
typedef struct s_cylinder
{
	t_obj_type	object_type;
	t_vec3		center;
	t_vec3		orientation;
	double		radius;
	double		height;
	t_color		color;

}	t_cylinder;

/**
Union to store different types of geometric objects.

Allows a single data structure to hold one of the following object types
at a time:
 - t_sphere `sp`:		Represents a sphere object in the scene.
 - t_plane `pl`:		Represents a plane object in the scene.
 - t_cylinder `cy`:		Represents a cylinder object in the scene.
*/
typedef union u_object_data
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}	t_obj_data;

typedef struct s_scene_object_node	t_obj_node; // Forward declaration

//#########
//# SCENE #
//#########

/**
Structure representing the ambient light in the scene.
- double `ratio`:	The ratio of the ambient lightning [0.0-1.0]
- t_color `color`:	The color of the ambient light.
 */
typedef struct s_ambi_light
{
	double		ratio;
	t_color		color;
}	t_ambi_light;

/**
Structure representing a light source in the scene.
- t_vec3 `position`:	The position of the light source.
- double `ratio`:		The ratio of the light brightness [0.0-1.0]
*/
typedef struct s_light
{
	t_vec3		position;
	double		ratio;
}	t_light;

/**
Structure representing the camera in the scene.
- t_vec3 `position`:		The position of the camera.
- t_vec3 `orientation`:		The orientation of the camera.
- double `fov`:				The field of view of the camera [0, 180].
*/
typedef struct s_camera
{
	t_vec3		position;
	t_vec3		orientation;
	double		fov;
}	t_cam;

/**
Structure representing the entire scene.
- t_ambi_light `ambient_light`:	The ambient light in the scene.
- t_light `light`:				The light source in the scene.
- t_cam `cam`:					The camera in the scene.
- t_list `objs`:				Linked list of objects in the scene.
*/
typedef struct s_scene
{
	t_ambi_light	ambi_light;
	t_light			light;
	t_cam			cam;
	t_list			*objs;
}	t_scene;

//################
//# TRIGONOMETRY #
//################

/**
Data structure holding trigonometric properties.
This is used to calculate the camera's field of view (FOV) and the
viewport's size.
- double angle_a:  Angle at vertex A in degrees (typically 90 degrees).
- double angle_b:  Angle at vertex B in degrees (half of the camera's FOV).
- double angle_c:  Angle at vertex C in degrees (calculated as 180 - angle_a - angle_b).
- double rad_a:    Angle at vertex A in radians.
- double rad_b:    Angle at vertex B in radians.
- double rad_c:    Angle at vertex C in radians.
- double cote_ab:  Length of the side between vertices A and B (typically 1 unit).
- double cote_bc:  Length of the side between vertices B and C.
- double cote_ca:  Length of the side between vertices C and A.
*/
// typedef struct s_trigo
// {
// 	double			angle_a;
// 	double			angle_b;
// 	double			angle_c;
// 	double			rad_a;
// 	double			rad_b;
// 	double			rad_c;
// 	double			cote_ab;
// 	double			cote_bc;
// 	double			cote_ca;
// }	t_trigo;

/**
Viewport: Rectangular area of the screen where the scene is projected.
Defines the portion of the scene that is visible to the camera and maps the 3D
scene to the 2D coordinates of the screen / image.
 */
// typedef struct s_viewport
// {
// 	t_trigo			trigo;
// 	double			min_x;
// 	double			max_x;
// 	double			min_y;
// 	double			max_y;
// 	double			width;
// 	double			height;
// 	double			***points;
// 	double			hypothenuse;
// 	double			aigu;
// 	double			win_ratio;
// 	t_vec3			local_right;
// 	t_vec3			local_up;
// 	t_vec3			local_down;
// }	t_viewport;

//####################
//# MAIN DATA STRUCT #
//####################

/**
Data structure holding all raytracing-related data.
- t_mlx `mlx`:	Struct with rendering context containing MiniLibX components.
*/
typedef struct s_rt
{
	t_mlx	mlx;
	t_scene	scene;
}	t_rt;

#endif
