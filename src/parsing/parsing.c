/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:47 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/13 18:13:41 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_unique_identifier(t_pars *parsing)
{
	if (parsing->elem_data[0][0] == 'A')
	{
		if (parsing->a_found)
			return (1);
		else
			parsing->a_found = 1;
	}
	if (parsing->elem_data[0][0] == 'C')
	{
		if (parsing->c_found)
			return (1);
		else
			parsing->c_found = 1;
	}
	if (parsing->elem_data[0][0] == 'L')
	{
		if (parsing->l_found)
			return (1);
		else
			parsing->l_found = 1;
	}
	if (parsing->elem_data[0][1])
		return (1);
	return (0);
}

int	check_single_element(t_scene *scene)
{
	if (scene->pars.elem_data[0][0] == 'A')
		parse_ambience(scene);
	// else if (parsing->elem_data[0][0] == 'C')
	// 	parse_camera(parsing);
	// else if (parsing->elem_data[0][0] == 'L')
	// 	parse_light(parsing);
	// else if (ft_strcmp(parsing->elem_data[0], "sp"))
	// 	parse_sphere(parsing);
	// else if (ft_strcmp(parsing->elem_data[0], "pl"))
	// 	parse_plane(parsing);
	// else if (ft_strcmp(parsing->elem_data[0], "cy"))
	// 	parse_cylinder(parsing);
	// else
	return (scene->pars.error_code);
}

/*Takes ONE line (one element), and uses ft_split to split it by spaces.
Calls check_unique_identifier to see that there are no duplicates of the
uppercase objects, and then makes a proper check for each field of the
element, by calling check_single_element.*/
int	check_elements(t_scene *scene)
{
	scene->pars.elem_data = ft_split(scene->pars.element, ' ');
	if (!scene->pars.elem_data)
		return (4);
	if (check_unique_identifier(&scene->pars))
		return (5);
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
		scene->pars.error_code = 6;
	while (scene->pars.element)
	{
		scene->pars.error_code = check_elements(scene);
		if (scene->pars.error_code != 0)
		{
			get_next_line(-1);
			break ;
		}
		free(scene->pars.element);
		scene->pars.element = get_next_line(scene->pars.fd);
	}
	return (scene->pars.error_code);
}

void	parsing(int argc, char **argv)
{
	t_scene	scene;

	init_scene(&scene);
	if (argc != 2)
		errors_file(1);
	if (check_file_extension(argv[1]))
		errors_file(2);
	if (check_file_existence(argv[1]))
		errors_file(3);
	file_line_by_line(&scene, argv[1]);
	if (scene.pars.error_code != 0)
		errors_parsing(&scene.pars);
}
