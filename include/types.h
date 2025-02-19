/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:55:37 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/19 13:07:38 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Defines the types and data structures used in the raytracer program.
*/

#ifndef TYPES_H
# define TYPES_H

# include "libft.h"	// for 't_list' definition
# include "parsing.h" // for 't_pars' definition

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
 - int `endian`:	Endianness refers to the byte order in which data types are
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
 - double `x`:	The x-coordinate/-component of the point / vector.
 - double `y`:	The y-coordinate/-component of the point / vector.
 - double `z`:	The z-coordinate/-component of the point / vector.
*/
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/**
Structure representing a color in RGB format:
 - unsigned char `r`:	The red component of the color [0-255].
 - unsigned char `g`:	The green component of the color [0-255].
 - unsigned char `b`:	The blue component of the color [0-255].
*/
typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

/**
Structure for storing values used in ray-object intersection calculations,
primarily for quadratic equation solutions (e.g., spheres, cylinders).
 - double `a`: 				Coefficient of t² in the quadratic equation.
 - double `b`:				Coefficient of t in the quadratic equation.
 - double `c`:				Constant term in the quadratic equation.
 - douboe `discriminant`:	The discriminant of the quadratic equation, used to
							determine if real solutions exist.
 - t_vec 3`oc`:				Vector from the object's center to the ray origin.
 - double `axis_dot_oc`:	Dot product between the object's axis vector and
							`oc`, used for cylinder intersections.
 - double `axis_dot_ray`:	Dot product between the object's axis vector and
 							the ray direction, used for cylinder intersections.
*/
typedef struct s_quadratic_solution
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vec3	oc;
	double	axis_dot_oc;
	double	axis_dot_ray;
}	t_quad;

/**
Structure for storing shadow ray data.
 - t_vec3 `dir`:	The normalized direction of the ray.
 - t_vec3 `ori`:	The starting point of the ray.
 - double `len`:	The length of the ray (shadow origin to light source).
*/
typedef struct s_shadow_ray
{
	t_vec3	dir;
	t_vec3	ori;
	double	len;
}	t_shdw;

//#################
//# INTERSECTIONS #
//#################

/**
Enumeration representing if a cap was hit during cylinder intersection.
 - NO_HIT:		0
 - TOP_CAP:		1
 - BOTTOM_CAP:	2
*/
typedef enum e_cap_hit
{
	NO_HIT,
	TOP_CAP,
	BOTTOM_CAP
}	t_cap_hit;

/**
Stores the data of the closest intersection between a ray and an object.
 - t_obj `*hit_obj`:	Pointer to the closest obj that the ray intersects with.
 - double `t_hit`:		The closest intersection distance for the ray.
 - t_vec3 `hit_point`:	The point where the ray intersects the object.
 - int `ixn_color`:		The color of the closest intersection.
*/
typedef struct s_intersection_data
{
	t_obj		*hit_obj;
	double		t_hit;
	t_vec3		hit_point;
	t_cap_hit	cap_hit;
}	t_ix;

//###########
//# OBJECTS #
//###########

/**
Enumeration representing different types of 3D objects.
 - PLANE:		0
 - SPHERE:		1
 - CYLINDER:	2
*/
typedef enum e_object_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_obj_type;

/**
Structure representing a plane in 3D space:
 - t_vec3 `point_in_plane`:	A point that lies on the plane.
 - t_vec3 `normal`:			A normalized vector representing the plane's normal,
							which is perpendicular to the plane's surface.
*/
typedef struct s_plane
{
	t_vec3		point_in_plane;
	t_vec3		normal;
}	t_plane;

/**
Structure representing a sphere in 3D space.
 - t_vec3 `center`:			The center point of the sphere.
 - double `radius`:			The radius of the sphere.
*/
typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
}	t_sphere;

/**
Structure representing a cylinder in 3D space:
 - t_vec3 `center`:			The center point of the cylinder's axis.
 - t_vec3 `orientation`:	A normalized vector representing the cylinder's axis.
 - double `radius`:			The radius of the cylinder.
 - double `radius_sqrd`:	The square of the cylinder's radius.
 - double `height`:			The height of the cylinder.
 - double `height_half`:	Half of the cylinder's height.
 - t_vec3 `cap_top_center`:		The center point of the cylinder's top cap.
 - t_vec3 `cap_bottom_center`:	The center point of the cylinder's bottom cap.
 - t_vec3 `cap_top_normal`:		The normal vector of the top cap
 								(same as `orientation`).
 - t_vec3 `cap_bottom_normal`:	The normal vector of the bottom cap.
*/
typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		orientation;
	double		radius;
	double		radius_sqrd;
	double		height;
	double		height_half;
	t_vec3		cap_top_center;
	t_vec3		cap_bottom_center;
	t_vec3		cap_top_normal;
	t_vec3		cap_bottom_normal;
}	t_cylinder;

/**
Union to store different types of geometric objects.

Allows a single data structure to hold one of the following object types
at a time:
 - t_sphere `sp`:		Represents a sphere object.
 - t_plane `pl`:		Represents a plane object.
 - t_cylinder `cy`:		Represents a cylinder object.
*/
typedef union u_object_specific
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}	t_obj_x;

/**
Structure representing a 3D object in the scene.
 - t_obj_type `object_type`:	The type of the object.
 - t_obj_x `x`:					Union holding the specific object data.
 - t_color `color`:				The color of the object.
 - int `color_in_amb`:			Color of the object in ambient light (hex value).
 - int `cam_in_obj`:			Flag indicating if the camera is inside the
 								object (not relevant for planes).
*/
typedef struct u_object
{
	t_obj_type	object_type;
	t_obj_x		x;
	t_color		color;
	int			color_in_amb;
	int			cam_in_obj;
}	t_obj;

//#########
//# SCENE #
//#########

/**
Structure representing the ambient light in the scene.
 - double `ratio`:		The ratio of the ambient lightning [0.0-1.0]
 - t_color `color`:		The color of the ambient light.
*/
typedef struct s_ambi_light
{
	double		ratio;
	t_color		color;
}	t_ambi_light;

/**
Structure representing the light source in the scene.
 - t_vec3 `position`:	The position of the light source.
 - double `ratio`:		The ratio of the light brightness [0.0-1.0]
 - t_color `color`:		The color of the light source.
*/
typedef struct s_light
{
	t_vec3		position;
	double		ratio;
	t_color		color;
}	t_light;

/**
Structure representing the camera in the scene.
 - t_vec3 `pos`:			Camera position in world coordinates.
 - t_vec3 `dir`:			Forward direction of the camera (normalized).
 - double `fov`:			Horizontal field of view [0, 180].
 - double `scale`:			Scaling factor, derived from FOV.
 - double `aspect_ratio`:	Screen aspect ratio.
  - t_vec3 `right`:			Right vector, perpendicular to orientation and up
							(used for world-space orientation).
 - t_vec3 `up`:				Up vector perpendicular to right and orientation
							(used for world-space orientation).
*/
typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		dir;
	double		fov;
	double		scale;
	double		aspect_ratio;
	t_vec3		right;
	t_vec3		up;
}	t_cam;

/**
Structure representing the entire scene.
 - t_pars `pars`:				Structure holding parsing data.
 - t_ambi_light `ambi_light`:	The ambient light in the scene.
 - t_light `light`:				The light source in the scene.
 - t_cam `cam`:					The camera in the scene.
 - t_list `objs`:				Linked list of objects in the scene.
*/
typedef struct s_scene
{
	t_pars			pars;
	t_ambi_light	ambi_light;
	t_light			light;
	t_cam			cam;
	t_list			*objs;
}	t_scene;

//####################
//# MAIN DATA STRUCT #
//####################

/**
Data structure holding all raytracing-related data.
- t_mlx `mlx`:		Struct with rendering context containing MiniLibX components.
- t_scene `scene`:	Struct with scene data, including objects, lights, and camera.
*/
typedef struct s_rt
{
	t_mlx	mlx;
	t_scene	scene;
}	t_rt;

#endif
