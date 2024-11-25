/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error_and_return.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:58:15 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/25 18:22:56 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_error_and_return(char **arr, int *parsing_error, int error_code)
{
	if (arr)
		ft_freearray(arr);
	*parsing_error = error_code;
	return (error_code);
}
