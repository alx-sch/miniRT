/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:24:44 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/14 14:39:14 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains hook functions to intercept and respond to user input,
including key input and window interaction events.
*/

#include "main.h"

// IN FILE:

int	handle_keypress(int keycode, t_rt *rt);
int	handle_window_close(t_rt *rt);

/**
Handles key press events:
- Esc:				The window is closed, all allocated memory is freed,
					and the program terminates successfully.

 @param keycode 	The key code of the pressed key.
 @param rt 			Pointer to the main structure of the program.

 @return  			`0` on success (no specific action taken).
*/
int	handle_keypress(int keycode, t_rt *rt)
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

 @param rt 		Pointer to the main structure of the program.

 @return 		`0` on success (no specific action taken).
*/
int	handle_window_close(t_rt *rt)
{
	cleanup(&rt);
	exit(EXIT_SUCCESS);
	return (0);
}
