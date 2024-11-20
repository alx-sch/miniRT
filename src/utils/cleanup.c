/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/19 15:56:17 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions for deallocating memory, resetting pointers to
NULL, and closing open file descriptors, ensuring proper cleanup after program
execution or whenever the program terminates unexpectedly.
*/

#include "main.h"

// IN FILE:

void	cleanup(t_rt **rt_ptr);

/**
Frees all resources associated with the mlx components and sets all pointers
to NULL for the window, image, and display (connection to X11 display server).

 @param rt 	Pointer to the main structure of the program.
*/
static void	cleanup_mlx(t_rt *rt)
{
	if (rt->mlx.mlx_ptr)
	{
		if (rt->mlx.win_ptr)
			(void)mlx_destroy_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr);
		if (rt->mlx.img.img_ptr)
			(void)mlx_destroy_image(rt->mlx.mlx_ptr, rt->mlx.img.img_ptr);
		(void)mlx_destroy_display(rt->mlx.mlx_ptr);
		free(rt->mlx.mlx_ptr);
		rt->mlx.win_ptr = NULL;
		rt->mlx.img.img_ptr = NULL;
		rt->mlx.img.data_ptr = NULL;
		rt->mlx.mlx_ptr = NULL;
	}
}

/**
Frees and closes all resources allocated for the raytracing structure,
including any MLX-related resources. EXPAND IF MORE FREE CALLS ADDED

 @param rt_ptr 	Double pointer to the main structure of the program.
				If `NULL` is passed, the function returns immediately without
				any cleanup (avoids access of uninitialized struct).
*/
void	cleanup(t_rt **rt_ptr)
{
	t_rt	*rt;

	if (!rt_ptr || !*rt_ptr)
		return ;
	rt = *rt_ptr;
	cleanup_mlx(rt);
	// Add more free calls here
	free(rt);
	*rt_ptr = NULL;
}
