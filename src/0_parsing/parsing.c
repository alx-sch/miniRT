/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:47 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/13 00:03:19 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Takes ONE line (one element), and uses ft_split to split it by spaces.
Calls check_unique_identifier to see that there are no duplicates of the
uppercase objects, and then makes a proper check for each field of the
element, by calling check_single_element.*/
int	file_one_line(t_scene *scene)
{
	scene->pars.elem_data = ft_split_by_spaces(scene->pars.element);
	if (!scene->pars.elem_data)
		return (ERR_MEM_ALLOC);
	if (check_unique_identifier(&scene->pars, scene->pars.elem_data[0]))
		return (ERR_UNIQUE_ELEM);
	scene->pars.error_code = check_and_set_single_element(scene);
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
		scene->pars.error_code = ERR_FILE_EMPTY;
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

/*Parses through the .rt-file, to check that all input is valid.
Sets the ambience, camera and light values to the input values,
but NOT the cylinders, spheres and planes.
Exits program with an error code and prints error message upon error.*/
static void	parsing(t_rt *rt, t_scene *scene, char *file)
{
	file_line_by_line(scene, file);
	if (scene->pars.error_code != 0)
		errors_parsing(rt, scene, &scene->pars);
	if (!all_necessary_identifiers(&scene->pars))
		errors_file(ERR_MISSING_IDENTIFIER, rt);
}

/*Checks that the file that's passed as argument to the program is valid input.
Both the file itself, but also its content. See more of what is
looked for in 'parsing.h'.
Prints an error message, and exits with a set error code upon error.
Returns the t_scene struct upon success.*/
void	parse_and_set_objects(t_rt *rt, int argc, char **argv)
{
	if (argc != 2)
		errors_file(ERR_USAGE, rt);
	if (check_file_existence(argv[1]))
		errors_file(ERR_FILE_ACCESS, rt);
	if (check_file_extension(argv[1]))
		errors_file(ERR_FILE_EXTENSION, rt);
	parsing(rt, &rt->scene, argv[1]);
	if (rt->scene.pars.error_code != 0)
		errors_parsing(rt, &rt->scene, &rt->scene.pars);
	adjust_color(&rt);
}
