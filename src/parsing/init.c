/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:58:28 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 16:53:40 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_parsing(t_pars *parsing)
{
	parsing->a_found = 0;
	parsing->l_found = 0;
	parsing->c_found = 0;
	parsing->fd = -1;
	parsing->error_code = 0;
	parsing->elem_data = NULL;
	parsing->element = NULL;
}

void	init_scene(t_scene *scene)
{
	init_parsing(&scene->pars);
	scene->amb_light = 0;
	scene->amb_color_r = 0;
	scene->amb_color_g = 0;
	scene->amb_color_b = 0;
	scene->cam_x = 0;
	scene->cam_y = 0;
	scene->cam_z = 0;
	scene->cam_vec_x = 0;
	scene->cam_vec_y = 0;
	scene->cam_vec_z = 0;
	scene->cam_hfov = 0;
	scene->light_x = 0;
	scene->light_y = 0;
	scene->light_z = 0;
	scene->light_bright = 0;
	scene->light_color_r = 0;
	scene->light_color_g = 0;
	scene->light_color_b = 0;
}
