/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:17:45 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/06 15:39:34 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Frees the scene struct.*/
void	free_scene(t_scene *scene)
{
	t_list	*temp;

	if (scene)
	{
		while (scene->objs)
		{
			temp = scene->objs->next;
			if (scene->objs->content)
				free(scene->objs->content);
			free(scene->objs);
			scene->objs = temp;
		}
	}
}

/*Frees the scene struct, the parsing struct within the scene struct, and 
exits with correct error code.*/
void	free_scene_and_exit(t_scene *scene, t_rt *rt)
{
	t_list	*temp;
	int		exit_code;

	exit_code = scene->pars.error_code;
	if (scene)
	{
		free_parsing(&scene->pars);
		while (scene->objs)
		{
			temp = scene->objs->next;
			if (scene->objs->content)
				free(scene->objs->content);
			free(scene->objs);
			scene->objs = temp;
		}
	}
	free(rt);
	exit(exit_code);
}
