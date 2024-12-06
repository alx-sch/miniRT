/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:00:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/06 16:00:33 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
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
Function used within the wrapper function `ft_lstclear()` to delete and
clean up the linked list nodes used for object parsinb.
*/
void	del_token(void *content)
{
	t_obj_data	*obj_data;

	obj_data = (t_obj_data *)content;
	if (!obj_data)
		return ;
	free(obj_data);
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
	ft_lstclear(&rt->scene.objs, del_token);
	free(rt);
	*rt_ptr = NULL;
}
