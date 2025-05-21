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
void	free_scene_and_exit(t_scene *scene, t_rt *rt, int missing_id)
{
	t_list	*temp;
	int		exit_code;

	exit_code = scene->pars.error_code;
	if (scene)
	{
		if (!missing_id)
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
