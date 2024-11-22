/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:17:45 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/22 15:27:04 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_scene(t_scene *scene)
{
	if (scene)
	{
		if (scene->pl)
			free(scene->pl);
		if (scene->cy)
			free(scene->cy);
		if (scene->sp)
			free(scene->sp);
	}
}

void	free_scene_and_exit(t_scene *scene)
{
	if (scene)
	{
		free_parsing(&scene->pars);
		if (scene->pl)
			free(scene->pl);
		if (scene->cy)
			free(scene->cy);
		if (scene->sp)
			free(scene->sp);
	}
	exit(scene->pars.error_code);
}
