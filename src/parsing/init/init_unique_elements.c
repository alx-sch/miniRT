/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_unique_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:09:59 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 16:52:54 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Initializes all values of the t_amb struct to 0.*/
void	init_ambience(t_amb *amb)
{
	amb->light = 0;
	amb->color_r = 0;
	amb->color_g = 0;
	amb->color_b = 0;
}

/*Initializes all values of the t_cam struct to 0.*/
void	init_camera(t_cam *cam)
{
	cam->x = 0;
	cam->y = 0;
	cam->z = 0;
	cam->vec_x = 0;
	cam->vec_y = 0;
	cam->vec_z = 0;
	cam->field = 0;
}

/*Initializes all values of the t_light struct to 0.*/
void	init_light(t_light *light)
{
	light->x = 0;
	light->y = 0;
	light->z = 0;
	light->bright = 0;
	light->color_r = 0;
	light->color_g = 0;
	light->color_b = 0;
}
