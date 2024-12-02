/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:08:40 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/29 16:24:06 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Utility functions for working with quadratic equations. For more info on
quadratic equations and the functions in this file, see the README:
https://github.com/Busedame/miniRT/blob/main/README.md#quadratic-equation
*/

#include "main.h"

// IN FILE:

double	calculate_discriminant(double a, double b, double c);
double	calculate_entry_distance(double a, double b, double discriminant);
double	calculate_exit_distance(double a, double b, double discriminant);

/**
Calculates the discriminant of a quadratic equation `ax^2 + bx + c = 0`, which
solves into `x = (-b ± sqrt(b^2 - 4ac)) / 2a`.

The discriminant `D = b^2 - 4ac` tells us:
- if `D > 0`, there are two real roots (the ray intersects the object at two
  points).
- if `D = 0`, there is one real root (the ray is tangent to the object, touching
  it at one point).
- if `D < 0`, there are no real roots (the ray does not intersect the object).

 @param a 	The coefficient of the quadratic term in quadratic equation.
 @param b 	The coefficient of the linear term in quadratic equation.
 @param c 	The constant term in quadratic equation.

 @return 	The discriminant of the quadratic equation.
*/
double	calculate_discriminant(double a, double b, double c)
{
	double	discriminant;

	discriminant = (b * b) - (4.0 * a * c);
	return (discriminant);
}

/**
Calculates the distance to the entry point of a ray with an object using the
quadratic equation `t1 = (-b - sqrt(b^2 - 4ac)) / 2a`.

 @param a 				The coefficient of the quadratic term.
 @param b 				The coefficient of the linear term.
 @param discriminant 	The discriminant of the quadratic equation (`b^2 - 4ac`).

 @return 				The smaller root solution (`t1` value) of the
 						quadratic equation.
*/
double	calculate_entry_distance(double a, double b, double discriminant)
{
	double	t1;

	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	return (t1);
}

/**
Calculates the distance to the exit point of a ray with an object using the
quadratic equation `x = (-b + sqrt(b^2 - 4ac)) / 2a`.

 @param a 				The coefficient of the quadratic term.
 @param b 				The coefficient of the linear term.
 @param discriminant 	The discriminant of the quadratic equation (`b^2 - 4ac`).

 @return 				The larger root solution (`t2` value) of the
 						quadratic equation.
*/
double	calculate_exit_distance(double a, double b, double discriminant)
{
	double	t2;

	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	return (t2);
}
