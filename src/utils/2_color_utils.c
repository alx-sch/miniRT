/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pixel_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:23:53 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/20 23:02:56 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Utility functions for working with pixels in the image buffer.
*/

#include "main.h"

// IN FILE:

int		color_to_hex(t_color color);
void	set_pixel_color(t_img *img, int x, int y, int color);

/**
Converts an RGB color to its hexadecimal representation.

This function takes a `t_color` structure containing the red, green, and blue
components of a color (each in the range [0-255]) and combines them into a single
integer in the format `0xRRGGBB`.
 @param color 	The color struct containing the red, green, and blue components.

 @return		An integer representing the color in hexadecimal format.
*/
int	color_to_hex(t_color color)
{
	int	hex;

	hex = color.r << 16 | color.g << 8 | color.b;
	return (hex);
}

/**
Sets the color of a pixel at a specified position within the image buffer.

The function calculates the index of the pixel in the image buffer and assigns
the given color value at that position.

The image buffer is treated as a 1D array, where each pixel's color is
represented as an integer (typically in the RGB format, 4 bytes per pixel
(3 bytes for RGB, 1 byte for padding or alpha channel).

- `y * WINDOW_W`:	This part calculates the starting index of the pixel row in
					the image buffer, based on the `y` coordinate.
					`WINDOW_W` is the width of the image.
- `x`:				This part adds the offset within the row, based on the `x`
					coordinate of the pixel.

 @param img 	Pointer to the image structure containing the image buffer.
 @param x 		The x-coordinate of the pixel.
 @param y 		The y-coordinate of the pixel.
 @param color 	The color value to set for the pixel as a hexadecimal integer.

 @note
Used as a more performative alternative to native `mlx_pixel_put()`. Source:
https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html#util-functions
*/
void	set_pixel_color(t_img *img, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = (y * WINDOW_W) + x;
	img->data_ptr[pixel_index] = color;
}
