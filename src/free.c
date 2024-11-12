/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/12 17:37:42 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions for deallocating memory, resetting pointers to
NULL, and closing open file descriptors, ensuring proper cleanup after program
execution or whenever the program terminates unexpectedly.
*/

#include "main.h"

// IN FILE:

void	free_fdf(t_rt **rt_ptr);

/**
Frees all resources associated with the mlx components and set all pointers
to NULL for the window, image, and display (connection to X11).

 @param rt 	Pointer to the main structure of the program.
*/
static void	free_mlx(t_rt *rt)
{
	if (rt->mlx.mlx)
	{
		if (rt->mlx.win)
			(void)mlx_destroy_window(rt->mlx.mlx, rt->mlx.win);
		if (rt->mlx.img.img)
			(void)mlx_destroy_image(rt->mlx.mlx, rt->mlx.img.img);
		(void)mlx_destroy_display(rt->mlx.mlx);
		free(rt->mlx.mlx);
		rt->mlx.win = NULL;
		rt->mlx.img.img = NULL;
		rt->mlx.img.data = NULL;
		rt->mlx.mlx = NULL;
	}
}

/**
Frees/closes all resources allocated for the raytracing structure, including
mlx-related ressources, ....

 @param rt_ptr	Pointer to the main structure of the program.
*/
void	free_rt(t_rt **rt_ptr)
{
	t_rt	*rt;

	rt = *rt_ptr;
	if (!rt)
		return ;
	free_mlx(rt);
	// Add more free calls here
	free(rt);
	*rt_ptr = NULL;
}
