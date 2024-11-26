/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:17:45 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 16:47:29 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Frees the scene struct.*/
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

/*Frees the scene struct, the parsing struct within the scene struct, and 
exits with correct error code.*/
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
