/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:55:16 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/14 14:42:11 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Defines constants for error messages and formatting styles.
*/

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_COLOR			"\033[91m\033[1m" // red and bold
# define RESET				"\033[0m"

# define ERR_ARG			"Invalid argument(s)! Use: './minirt <scene.rt>'"
# define ERR_FILE_TYPE		"Invalid file format! Use: './minirt <scene.rt>'"
# define ERR_MALLOC			"malloc() failed"

#endif
