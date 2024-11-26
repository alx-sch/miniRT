/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:00:50 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 16:48:53 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Prints out a parsing related error message for a cylinder object.*/
void	cylinder_errors(t_pars *parsing, int count)
{
	if (parsing->error_code == ERR_CY_FIELDS)
		ft_putstr_fd(ERR_MSG_CY_FIELDS, 2);
	else if (parsing->error_code == ERR_CY_COOR_FIELDS)
		ft_putstr_fd(ERR_MSG_CY_COOR_FIELDS, 2);
	else if (parsing->error_code == ERR_CY_COOR_VALUES)
		ft_putstr_fd(ERR_MSG_CY_COOR_VALUES, 2);
	else if (parsing->error_code == ERR_CY_VECTOR_FIELDS)
		ft_putstr_fd(ERR_MSG_CY_VECTOR_FIELDS, 2);
	else if (parsing->error_code == ERR_CY_VECTOR_VALUES)
		ft_putstr_fd(ERR_MSG_CY_VECTOR_VALUES, 2);
	else if (parsing->error_code == ERR_CY_VECTOR_NORM)
		ft_putstr_fd(ERR_MSG_CY_VECTOR_NORM, 2);
	else if (parsing->error_code == ERR_CY_DM)
		ft_putstr_fd(ERR_MSG_CY_DM, 2);
	else if (parsing->error_code == ERR_CY_HEIGHT)
		ft_putstr_fd(ERR_MSG_CY_HEIGHT, 2);
	else if (parsing->error_code == ERR_CY_COLOR_FIELDS)
		ft_putstr_fd(ERR_MSG_CY_COLOR_FIELDS, 2);
	else if (parsing->error_code == ERR_CY_COLOR_VALUES)
		ft_putstr_fd(ERR_MSG_CY_COLOR_VALUES, 2);
	printf("Cylinder number: %d\n", count);
}

/*Prints out a parsing related error message for a plane object.*/
void	plane_errors(t_pars *parsing, int count)
{
	if (parsing->error_code == ERR_PL_FIELDS)
		ft_putstr_fd(ERR_MSG_PL_FIELDS, 2);
	else if (parsing->error_code == ERR_PL_COOR_FIELDS)
		ft_putstr_fd(ERR_MSG_PL_COOR_FIELDS, 2);
	else if (parsing->error_code == ERR_PL_COOR_VALUES)
		ft_putstr_fd(ERR_MSG_PL_COOR_VALUES, 2);
	else if (parsing->error_code == ERR_PL_VECTOR_FIELDS)
		ft_putstr_fd(ERR_MSG_PL_VECTOR_FIELDS, 2);
	else if (parsing->error_code == ERR_PL_VECTOR_VALUES)
		ft_putstr_fd(ERR_MSG_PL_VECTOR_VALUES, 2);
	else if (parsing->error_code == ERR_PL_VECTOR_NORM)
		ft_putstr_fd(ERR_MSG_PL_VECTOR_NORM, 2);
	else if (parsing->error_code == ERR_PL_COLOR_FIELDS)
		ft_putstr_fd(ERR_MSG_PL_COLOR_FIELDS, 2);
	else if (parsing->error_code == ERR_PL_COLOR_VALUES)
		ft_putstr_fd(ERR_MSG_PL_COLOR_VALUES, 2);
	printf("Plane number: %d\n", count);
}

/*Prints out a parsing related error message for a sphere object.*/
void	sphere_errors(t_pars *parsing, int count)
{
	if (parsing->error_code == ERR_SP_FIELDS)
		ft_putstr_fd(ERR_MSG_SP_FIELDS, 2);
	else if (parsing->error_code == ERR_SP_COOR_FIELDS)
		ft_putstr_fd(ERR_MSG_SP_COOR_FIELDS, 2);
	else if (parsing->error_code == ERR_SP_COOR_VALUES)
		ft_putstr_fd(ERR_MSG_SP_COOR_VALUES, 2);
	else if (parsing->error_code == ERR_SP_DM)
		ft_putstr_fd(ERR_MSG_SP_DM, 2);
	else if (parsing->error_code == ERR_SP_COLOR_FIELDS)
		ft_putstr_fd(ERR_MSG_SP_COLOR_FIELDS, 2);
	else if (parsing->error_code == ERR_SP_COLOR_VALUES)
		ft_putstr_fd(ERR_MSG_SP_COLOR_VALUES, 2);
	printf("Sphere number: %d\n", count);
}
