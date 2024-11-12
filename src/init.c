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

 @param rt 	Pointer to the main structure of the program.
*/
void	init_mlx(t_rt *rt)
{
	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		perror_and_exit(ERR_MLX, rt);
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, WINDOW_W, WINDOW_H, WINDOW_TITLE);
	if (!rt->mlx.win)
		msg_and_exit(ERR_MLX, rt);
	rt->mlx.img.img = mlx_new_image(rt->mlx.mlx, WINDOW_W, WINDOW_H);
	rt->mlx.img.data = mlx_get_data_addr(rt->mlx.img.img, &rt->mlx.img.bpp,
			&rt->mlx.img.size_len, &rt->mlx.img.endian);
}
