/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:17:45 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/05 13:54:11 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Frees the scene struct.*/
void	free_scene(t_tmp_scene *scene)
{
	if (scene)
	{
		if (scene->plane)
			free(scene->plane);
		if (scene->cyl)
			free(scene->cyl);
		if (scene->sphere)
			free(scene->sphere);
	}
}

/*Frees the scene struct, the parsing struct within the scene struct, and 
exits with correct error code.*/
void	free_scene_and_exit(t_tmp_scene *scene)
{
	if (scene)
	{
		free_parsing(&scene->pars);
		if (scene->plane)
			free(scene->plane);
		if (scene->cyl)
			free(scene->cyl);
		if (scene->sphere)
			free(scene->sphere);
	}
	exit(scene->pars.error_code);
}
