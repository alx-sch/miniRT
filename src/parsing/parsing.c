/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:47 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/12 18:32:19 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_freearray(char **arr)
{
	int	crstr;
	int	max;

	crstr = 0;
	max = 0;
	while (arr[crstr])
	{
		crstr++;
		max++;
	}
	crstr = 0;
	while (crstr < max)
	{
		free(arr[crstr]);
		arr[crstr] = NULL;
		crstr++;
	}
	free(arr);
	arr = NULL;
	return (0);
}

static int	check_file_existence(char *str)
{
	if (access(str, R_OK) != 0)
		return (1);
	return (0);
}

static int	check_file_extension(char *str)
{
	int	end;

	end = ft_strlen(str);
	if (end < 4)
		return (1);
	if (str[end - 1] != 't')
		return (1);
	if (str[end - 2] != 'r')
		return (1);
	if (str[end - 3] != '.')
		return (1);
	return (0);
}

int	check_unique_identifier(t_pars *parsing)
{
	if (!ft_strcmp(parsing->elem_data[0], "A"))
	{
		if (parsing->a_found)
			return (1);
		else
			parsing->a_found = 1;
	}
	if (!ft_strcmp(parsing->elem_data[0], "C"))
	{
		if (parsing->c_found)
			return (1);
		else
			parsing->c_found = 1;
	}
	if (!ft_strcmp(parsing->elem_data[0], "L"))
	{
		if (parsing->l_found)
			return (1);
		else
			parsing->l_found = 1;
	}
	return (0);
}

int	check_element(t_pars *parsing)
{
	parsing->elem_data = ft_split(parsing->element, ' ');
	if (!parsing->elem_data)
	{
		free(parsing->element);
		return (1);
	}
	if (check_unique_identifier(parsing))
		return (1);
	ft_freearray(parsing->elem_data);
	return (0);
}

void	init_parsing(t_pars *parsing)
{
	parsing->a_found = 0;
	parsing->l_found = 0;
	parsing->c_found = 0;
	parsing->fd = -1;
	parsing->elem_data = NULL;
	parsing->element = NULL;
}

int	file_parsing(char *str)
{
	t_pars	parsing;

	init_parsing(&parsing);
	parsing.fd = open(str, O_RDONLY);
	parsing.element = get_next_line(parsing.fd);
	while (parsing.element)
	{
		if (check_element(&parsing))
			return (1);
		free(parsing.element);
		parsing.element = get_next_line(parsing.fd);
	}
	return (0);
}

void	parsing(int argc, char **argv)
{
	if (argc != 2)
		errors_parsing(1);
	if (check_file_extension(argv[1]))
		errors_parsing(2);
	if (check_file_existence(argv[1]))
		errors_parsing(3);
	if (file_parsing(argv[1]))
		errors_parsing(4);
}
