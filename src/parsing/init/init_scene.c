/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:58:28 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 16:52:35 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Initializes all values of the t_pars struct to 0.*/
void	init_parsing(t_pars *parsing)
{
	parsing->a_found = 0;
	parsing->l_found = 0;
	parsing->c_found = 0;
	parsing->fd = -1;
	parsing->error_code = 0;
	parsing->elem_data = NULL;
	parsing->element = NULL;
	parsing->cy_count = 0;
	parsing->pl_count = 0;
	parsing->sp_count = 0;
}

/*Initializes all values of the t_scene struct to 0.*/
void	init_scene(t_scene *scene)
{
	init_parsing(&scene->pars);
	init_ambience(&scene->amb);
	init_camera(&scene->cam);
	init_light(&scene->light);
	scene->sp = NULL;
	scene->pl = NULL;
	scene->cy = NULL;
	scene->tot_cy = 0;
	scene->tot_pl = 0;
	scene->tot_sp = 0;
}
