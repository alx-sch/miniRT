/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:58:28 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 17:33:53 by nholbroo         ###   ########.fr       */
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
	init_ambience(&scene->amb);
	init_camera(&scene->cam);
	init_light(&scene->light);
	init_sphere(&scene->sp);
	init_plane(&scene->pl);
	init_cylinder(&scene->cy);
}
