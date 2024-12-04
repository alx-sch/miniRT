/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_unique_elements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:45:05 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 16:49:09 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Prints out a parsing related error message for an ambience object.*/
void	ambience_errors(t_pars *parsing)
{
	if (parsing->error_code == ERR_AMB_FIELDS)
		ft_putstr_fd(ERR_MSG_AMB_FIELDS, 2);
	else if (parsing->error_code == ERR_AMB_LIGHT)
		ft_putstr_fd(ERR_MSG_AMB_LIGHT, 2);
	else if (parsing->error_code == ERR_AMB_COLOR_FIELDS)
		ft_putstr_fd(ERR_MSG_AMB_COLOR_FIELDS, 2);
	else if (parsing->error_code == ERR_AMB_COLOR_VALUES)
		ft_putstr_fd(ERR_MSG_AMB_COLOR_VALUES, 2);
}

/*Prints out a parsing related error message for a camera object.*/
void	camera_errors(t_pars *parsing)
{
	if (parsing->error_code == ERR_CAM_FIELDS)
		ft_putstr_fd(ERR_MSG_CAM_FIELDS, 2);
	else if (parsing->error_code == ERR_CAM_COOR_FIELDS)
		ft_putstr_fd(ERR_MSG_CAM_COOR_FIELDS, 2);
	else if (parsing->error_code == ERR_CAM_COOR_VALUES)
		ft_putstr_fd(ERR_MSG_CAM_COOR_VALUES, 2);
	else if (parsing->error_code == ERR_CAM_VECTOR_FIELDS)
		ft_putstr_fd(ERR_MSG_CAM_VECTOR_FIELDS, 2);
	else if (parsing->error_code == ERR_CAM_VECTOR_VALUES)
		ft_putstr_fd(ERR_MSG_CAM_VECTOR_VALUES, 2);
	else if (parsing->error_code == ERR_CAM_VECTOR_NORM)
		ft_putstr_fd(ERR_MSG_CAM_VECTOR_NORM, 2);
	else if (parsing->error_code == ERR_CAM_FIELD_OF_VIEW)
		ft_putstr_fd(ERR_MSG_CAM_FIELD_OF_VIEW, 2);
}

/*Prints out a parsing related error message for a light object.*/
void	light_errors(t_pars *parsing)
{
	if (parsing->error_code == ERR_LIGHT_FIELDS)
		ft_putstr_fd(ERR_MSG_LIGHT_FIELDS, 2);
	else if (parsing->error_code == ERR_LIGHT_COOR_FIELDS)
		ft_putstr_fd(ERR_MSG_LIGHT_COOR_FIELDS, 2);
	else if (parsing->error_code == ERR_LIGHT_COOR_VALUES)
		ft_putstr_fd(ERR_MSG_LIGHT_COOR_VALUES, 2);
	else if (parsing->error_code == ERR_LIGHT_BRIGHTNESS)
		ft_putstr_fd(ERR_MSG_LIGHT_BRIGHTNESS, 2);
	else if (parsing->error_code == ERR_LIGHT_COLOR_FIELDS)
		ft_putstr_fd(ERR_MSG_LIGHT_COLOR_FIELDS, 2);
	else if (parsing->error_code == ERR_LIGHT_COLOR_VALUES)
		ft_putstr_fd(ERR_MSG_LIGHT_COLOR_VALUES, 2);
}
