/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:36:36 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/15 13:06:05 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Initializes the MiniLibX components required for graphic rendering:
- Establishes the connection to the graphic system (rt->mlx.mlx).
- Creates the window (rt->mlx.win).
- Sets up the image buffer (rt->mlx.img).

 @note 	WINDOW_W and WINDOW_H are pre-compilation constants defined in Makefile.
		Adjust during compilation, e.g. `make WINDOW_W=1920 WINDOW_H=1080`.

 @param rt 	Pointer to the main structure of the program.
*/
void	init_mlx(t_rt *rt)
{
	errno = 0;
	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		cleanup_error_exit("mlx_init() failed", rt);
	errno = 0;
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, WINDOW_W, WINDOW_H, WINDOW_TITLE);
	if (!rt->mlx.win)
		cleanup_error_exit("mlx_new_window() failed", rt);
	errno = 0;
	rt->mlx.img.img = mlx_new_image(rt->mlx.mlx, WINDOW_W, WINDOW_H);
	if (!rt->mlx.img.img)
		cleanup_error_exit("mlx_new_image() failed", rt);
	errno = 0;
	rt->mlx.img.data = mlx_get_data_addr(rt->mlx.img.img, &rt->mlx.img.bpp,
			&rt->mlx.img.size_len, &rt->mlx.img.endian);
	if (!rt->mlx.img.data)
		cleanup_error_exit("mlx_get_data_addr() failed", rt);
	errno = 0;
}
