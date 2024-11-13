/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:47 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/13 17:23:04 by nholbroo         ###   ########.fr       */
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

int	check_single_element(t_pars *parsing)
{
	if (parsing->elem_data[0][0] == 'A')
		parse_ambience(parsing);
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
	return (parsing->error_code);
}

int	check_elements(t_pars *parsing)
{
	parsing->elem_data = ft_split(parsing->element, ' ');
	if (!parsing->elem_data)
		return (4);
	if (check_unique_identifier(parsing))
		return (5);
	parsing->error_code = check_single_element(parsing);
	if (parsing->error_code != 0)
		return (parsing->error_code);
	ft_freearray(parsing->elem_data);
	return (0);
}

int	file_line_by_line(t_pars *parsing, char *str)
{
	parsing->fd = open(str, O_RDONLY);
	parsing->element = get_next_line(parsing->fd);
	if (!parsing->element)
		parsing->error_code = 6;
	while (parsing->element)
	{
		parsing->error_code = check_elements(parsing);
		if (parsing->error_code != 0)
		{
			get_next_line(-1);
			break ;
		}
		free(parsing->element);
		parsing->element = get_next_line(parsing->fd);
	}
	return (parsing->error_code);
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
	file_line_by_line(&scene.pars, argv[1]);
	if (scene.pars.error_code != 0)
		errors_parsing(&scene.pars);
}
