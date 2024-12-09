/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:24:44 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/05 07:15:33 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains hook functions to intercept and respond to user input,
including key input and window interaction events.
*/

#include "main.h"

// IN FILE:

void	start_event_loop(t_rt *rt);

/**
Handles key press events:
- Esc:				The window is closed, all allocated memory is freed,
					and the program terminates successfully.

 @param keycode 	The key code of the pressed key.
 @param rt 			Pointer to the main structure of the program.

 @return  			`0` on success (no specific action taken).
*/
static int	handle_keypress(int keycode, t_rt *rt)
{
	if (keycode == XK_Escape)
	{
		cleanup(&rt);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

/**
Handles window close events:
If the destruction signal is received (by clicking the 'x' button),
the window is closed, all allocated memory is freed, and the program
terminates successfully.

 @param rt 	Pointer to the main structure of the program.

 @return 	`0` on success (no specific action taken).
*/
static int	handle_window_close(t_rt *rt)
{
	cleanup(&rt);
	exit(EXIT_SUCCESS);
	return (0);
}

/**
Sets up event hooks for and starts the MiniLibX event loop.

The event loop waits for and dispatches events (key presses and window close
events) to the appropriate handlers. The loop runs indefinitely until the
program is terminated.

 @param rt 	Pointer to the main structure of the program.
*/
void	start_event_loop(t_rt *rt)
{
	(void)mlx_key_hook(rt->mlx.win_ptr, &handle_keypress, rt);
	(void)mlx_hook(rt->mlx.win_ptr, DestroyNotify, 0, &handle_window_close, rt);
	(void)mlx_loop(rt->mlx.mlx_ptr);
}
