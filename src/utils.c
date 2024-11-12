/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:42 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/12 17:23:48 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions for terminating the program in a controlled manner
whenever an error occurs (such as invalid user input, failed file opening,
memory allocation errors, etc.). Before terminating the program, informative
error messages are printed to stderr, and all dynamically allocated memory
within the `rt` structure is deallocated.
*/

#include "main.h"

// IN FILE

void	msg_and_exit(char *msg, t_rt *rt);
void	perror_and_exit(char *msg, t_rt *rt);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/**
Prints an error message to stderr, frees memory allocated within the
rt structure and exits the program.

 @param msg 	Error message to print.
 @param rt 		Pointer to the main structure of the program.
*/
void	msg_and_exit(char *msg, t_rt *rt)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	free_rt(&rt);
	exit(EXIT_FAILURE);
}

/**
Prints an error message to stderr via perror(), which also prints the last
encountered error and frees memory allocated within the fdf structure.
Then, exits the program.

 @param msg 	Error message to print before the perror() message.
 @param rt 		Pointer to the main structure of the program.
*/
void	perror_and_exit(char *msg, t_rt *rt)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	perror(msg);
	ft_putstr_fd(RESET, STDERR_FILENO);
	free_rt(&rt);
	exit(EXIT_FAILURE);
}
