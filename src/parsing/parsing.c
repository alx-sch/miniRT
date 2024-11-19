/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:47 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/19 16:48:20 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Takes ONE line (one element), and uses ft_split to split it by spaces.
Calls check_unique_identifier to see that there are no duplicates of the
uppercase objects, and then makes a proper check for each field of the
element, by calling check_single_element.*/
int	file_one_line(t_scene *scene)
{
	scene->pars.elem_data = ft_split(scene->pars.element, ' ');
	if (!scene->pars.elem_data)
		return (ERR_MEM_ALLOC);
	if (check_unique_identifier(&scene->pars, scene->pars.elem_data[0]))
		return (ERR_UNIQUE_ELEM);
	scene->pars.error_code = check_single_element(scene);
	if (scene->pars.error_code != 0)
		return (scene->pars.error_code);
	ft_freearray(scene->pars.elem_data);
	return (0);
}

/*Uses get next line to get one line at a time (one element at a time). 
Passes it to check_elements for each line. Returns 0 upon success, or 
an error code indicating the issue upon error.*/
int	file_line_by_line(t_scene *scene, char *str)
{
	scene->pars.fd = open(str, O_RDONLY);
	scene->pars.element = get_next_line(scene->pars.fd);
	if (!scene->pars.element)
		scene->pars.error_code = ERR_MEM_ALLOC;
	while (scene->pars.element)
	{
		scene->pars.error_code = file_one_line(scene);
		if (scene->pars.error_code != 0)
		{
			get_next_line(-1);
			break ;
		}
		free(scene->pars.element);
		scene->pars.element = get_next_line(scene->pars.fd);
	}
	close(scene->pars.fd);
	return (scene->pars.error_code);
}

t_scene	parsing(int argc, char **argv)
{
	t_scene	scene;

	init_scene(&scene);
	if (argc != 2)
		errors_file(ERR_USAGE);
	if (check_file_extension(argv[1]))
		errors_file(ERR_FILE_EXTENSION);
	if (check_file_existence(argv[1]))
		errors_file(ERR_FILE_ACCESS);
	file_line_by_line(&scene, argv[1]);
	if (scene.pars.error_code != 0)
		errors_parsing(&scene.pars);
	return (scene);
}
