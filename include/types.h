/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:55:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/15 16:53:30 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Defines custom types and data structures.
*/

#ifndef TYPES_H
# define TYPES_H

//#######
//# MLX #
//#######

/*
Data structure holding image info, incl. dimensions, pixel data, color, and
endianess.
- void *`img`:	Pointer to image object. Used when manipulating image as a
				whole, e.g. loading into memory or passing to redering ftcs.
- int *`data`:	Pointer to the start of image data -> raw pixel information.
				Used in operations reading/modifying individual pixels, such
				as setting the color. int values represent whole pixels.
- int `bpp`:		Number of bits used to represent each pixel, holds the color.
- int `size_line`:	Length of each line in the image in bytes,
					indicating the number of bytes needed to store a single
					row of pixels in the image.
- int `endian`:	Endianness refers to the byte order in which data types are
				stored in memory (either big or little endian; left to right
				and right to left, respectively). Used to determine how to
				interpret image data ('img' and 'data' members).
*/
typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_line;
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
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

//#######
//# XXXX #
//#######

/*
Data structure representing a 3D vector.
- double `x`:		The x-coordinate of the vector.
- double `y`:		The y-coordinate of the vector.
- double `z`:		The z-coordinate of the vector.
*/
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

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
typedef struct s_trigo
{
	double			angle_a;
	double			angle_b;
	double			angle_c;
	double			rad_a;
	double			rad_b;
	double			rad_c;
	double			cote_ab;
	double			cote_bc;
	double			cote_ca;
}					t_trigo;

/**
Viewport: Rectangular area of the screen where the scene is projected.
Defines the portion of the scene that is visible to the camera and maps the 3D
scene to the 2D coordinates of the screen / image.
 */
typedef struct s_vp
{
	t_trigo			trigo;
	double			min_x;
	double			max_x;
	double			min_y;
	double			max_y;
	double			width;
	double			height;
	double			***points;
	double			hypothenuse;
	double			aigu;
	double			win_ratio;
	t_vec3			local_right;
	t_vec3			local_up;
	t_vec3			local_down;
}					t_vp;

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
	// Add more fields here
}	t_rt;

#endif
