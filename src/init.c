/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:36:36 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/12 17:42:53 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Initializes the MiniLibX components required for graphic rendering:
- Establishes the connection to the graphic system (rt->mlx.mlx).
- Creates the window (rt->mlx.win).
- Sets up the image buffer (rt->mlx.img).

 @note 	The errno is reset to `0` after calls to `mlx_init()`, `mlx_new_window()`,
		and `mlx_new_image()` as these functions set errno to `EAGAIN`/`EWOULDBLOCK`
		even when they succeed, which can cause false positives in error checking.

 @param rt 	Pointer to the main structure of the program.
*/
void	init_mlx(t_rt *rt)
{

	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		print_perror_and_exit("mlx_init() failed", rt);
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, WINDOW_W, WINDOW_H, WINDOW_TITLE);
	if (!rt->mlx.win)
		print_perror_and_exit("mlx_new_window() failed", rt);
	rt->mlx.img.img = mlx_new_image(rt->mlx.mlx, WINDOW_W, WINDOW_H);
	if (!rt->mlx.img.img)
		print_perror_and_exit("mlx_new_image() failed", rt);
	errno = 0;
	rt->mlx.img.data = mlx_get_data_addr(rt->mlx.img.img, &rt->mlx.img.bpp,
			&rt->mlx.img.size_len, &rt->mlx.img.endian);
	if (!rt->mlx.img.data)
		print_perror_and_exit("mlx_get_data_addr() failed", rt);
}
