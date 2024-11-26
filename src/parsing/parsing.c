/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:47 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 17:24:50 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Takes ONE line (one element), and uses ft_split to split it by spaces.
Calls check_unique_identifier to see that there are no duplicates of the
uppercase objects, and then makes a proper check for each field of the
element, by calling check_single_element.*/
int	file_one_line(t_scene *scene, int parse)
{
	scene->pars.elem_data = ft_split(scene->pars.element, ' ');
	if (!scene->pars.elem_data)
		return (ERR_MEM_ALLOC);
	if (!parse)
	{
		scene->pars.error_code = set_single_element(scene);
		ft_freearray(scene->pars.elem_data);
		return (0);
	}
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
int	file_line_by_line(t_scene *scene, char *str, int parse)
{
	scene->pars.fd = open(str, O_RDONLY);
	scene->pars.element = get_next_line(scene->pars.fd);
	if (!scene->pars.element)
		scene->pars.error_code = ERR_FILE_EMPTY;
	while (scene->pars.element)
	{
		scene->pars.error_code = file_one_line(scene, parse);
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
static void	parsing(t_scene *scene, char *file)
{
	file_line_by_line(scene, file, 1);
	if (scene->pars.error_code != 0)
		errors_parsing(scene, &scene->pars);
	if (!all_necessary_identifiers(&scene->pars))
		errors_file(ERR_MISSING_IDENTIFIER);
	if (allocate_nonunique_elements(scene) != 0)
		errors_parsing(scene, &scene->pars);
}

/*After everything has been parsed, the values of the nonunique-elements 
(cylinder, plane and sphere) are saved in the t_scene struct.*/
static void	set_nonunique_elements(t_scene *scene, char *file)
{
	file_line_by_line(scene, file, 0);
}

/*Checks that the file that's passed as argument to the program is valid input.
Both the file itself, but also its content. See more of what is 
looked for in 'parsing.h'.
Prints an error message, and exits with a set error code upon error.
Returns the t_scene struct upon success.*/
t_scene	parse_and_set_objects(int argc, char **argv)
{
	t_scene	scene;

	init_scene(&scene);
	if (argc != 2)
		errors_file(ERR_USAGE);
	if (check_file_existence(argv[1]))
		errors_file(ERR_FILE_ACCESS);
	if (check_file_extension(argv[1]))
		errors_file(ERR_FILE_EXTENSION);
	parsing(&scene, argv[1]);
	set_nonunique_elements(&scene, argv[1]);
	if (scene.pars.error_code != 0)
		errors_parsing(&scene, &scene.pars);
	return (scene);
}
