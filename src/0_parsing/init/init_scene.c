/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:58:28 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/06 15:38:29 by nholbroo         ###   ########.fr       */
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
}

/*Initializes all values of the t_scene struct to 0.*/
void	init_scene(t_scene *scene)
{
	init_parsing(&scene->pars);
	init_ambience(&scene->ambi_light);
	init_camera(&scene->cam);
	init_light(&scene->light);
	scene->objs = NULL;
}
