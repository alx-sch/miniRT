/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:55:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/12 17:34:49 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file defines custom types and data structures.
*/

#ifndef TYPES_H
# define TYPES_H

/*
Data structure holding image info, incl. dimensions, pixel data, color, and
endianess.
- void *img:	Pointer to image object. Used when manipulating image as a
				whole, e.g. loading into memory or passing to redering ftcs.
- char *data:	Pointer to the start of image data -> raw pixel information.
				Used in operations reading/modifying individual pixels, such
				as setting the color.
- int bpp:		Number of bits used to represent each pixel, holds the color.
- int size_len:	Length of each line in the image in bytes,
				indicating the number of bytes needed to store a single
				row of pixels in the image.
- int endian:	Endianness refers to the byte order in which data types are
				stored in memory (either big or little endian; left to right
				and right to left, respectively). Used to determine how to
				interpret image data ('img' and 'data' members).
*/
typedef struct s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_len;
	int		endian;
}	t_img;

/*
Data structure holding MiniLibX components for rendering the raytracer output.
- void *mlx:	Pointer to the MiniLibX context.
- void *win:	Pointer to the window object.
- t_img img:	Image structure containing pixel data, color, and endianess.
- int width:	Width of the window in pixels.
- int height:	Height of the window in pixels.
- char *title:	Title of the window.
*/
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		width;
	int		height;
	char	*title;
}	t_mlx;


/**
Data structure holding all raytracing-related data.
- t_render_ctx render_ctx:	Rendering context containing MiniLibX components.
*/
typedef struct s_raytracing
{
	t_mlx	mlx;
	// Add more fields here
}	t_raytracing;

typedef struct s_raytracing	t_rt; // Abbreviation for 't_raytracing'

#endif
