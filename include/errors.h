/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:55:16 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/04 09:43:24 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Defines constants for error messages and formatting styles.
*/

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_COLOR			"\001\033[91m\033[1m\002" // red and bold
# define RESET				"\001\033[0m\002"

# define ERR_ARG			"Invalid argument(s)! Use: './minirt <scene.rt>'"
# define ERR_FILE_TYPE		"Invalid file format! Use: './minirt <scene.rt>'"
# define ERR_MALLOC			"malloc() failed"

#endif
