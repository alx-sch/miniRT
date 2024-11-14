/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:03 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/13 23:32:46 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Sets up event hooks and starts the MiniLibX event loop.

This function sets up the necessary event hooks for handling key presses
and window destruction events. It then starts the MiniLibX event loop,
which waits for events and dispatches them to the appropriate handlers.
The event loop runs indefinitely until the program is terminated.

 @param rt 	Pointer to the main structure of the program.
*/
void	run_mlx(t_rt *rt)
{
	(void)mlx_key_hook(rt->mlx.win, &handle_keypress, rt);
	(void)mlx_hook(rt->mlx.win, DestroyNotify, 0, &handle_window_close, rt);
	(void)mlx_loop(rt->mlx.mlx);
}

int	main(void)
{
	t_rt	*rt;

	// check args / .rt file
	rt = malloc(sizeof(t_rt));
	if (!rt)
		cleanup_error_exit(ERR_MALLOC, NULL);
	// populate scene info into data struct (parse file)
	init_mlx(rt);
	run_mlx(rt);
	return (0);
}
