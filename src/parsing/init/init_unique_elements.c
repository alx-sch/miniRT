/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_unique_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:09:59 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/05 13:48:26 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Initializes all values of the t_amb struct to 0.*/
void	init_ambience(t_ambi_light *amb)
{
	amb->ratio = 0;
	amb->color.r = 0;
	amb->color.g = 0;
	amb->color.b = 0;
}

/*Initializes all values of the t_cam struct to 0.*/
void	init_camera(t_cam *cam)
{
	cam->position.x = 0;
	cam->position.y = 0;
	cam->position.z = 0;
	cam->orientation.x = 0;
	cam->orientation.y = 0;
	cam->orientation.z = 0;
	cam->fov = 0;
}

/*Initializes all values of the t_light struct to 0.*/
void	init_light(t_light *light)
{
	light->position.x = 0;
	light->position.y = 0;
	light->position.z = 0;
	light->ratio = 0;
	light->color.r = 0;
	light->color.g = 0;
	light->color.b = 0;
}
