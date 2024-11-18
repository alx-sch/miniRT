/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:00:50 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/18 19:03:22 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	sphere_errors(t_pars *parsing)
{
	if (parsing->error_code == ERR_SP_FIELDS)
		ft_putstr_fd(ERR_MSG_SP_FIELDS, 2);
	if (parsing->error_code == ERR_SP_COOR_FIELDS)
		ft_putstr_fd(ERR_MSG_SP_COOR_FIELDS, 2);
	if (parsing->error_code == ERR_SP_COOR_VALUES)
		ft_putstr_fd(ERR_MSG_SP_COOR_VALUES, 2);
	if (parsing->error_code == ERR_SP_DM)
		ft_putstr_fd(ERR_MSG_SP_DM, 2);
	if (parsing->error_code == ERR_SP_COLOR_FIELDS)
		ft_putstr_fd(ERR_MSG_SP_COLOR_FIELDS, 2);
	if (parsing->error_code == ERR_SP_COLOR_VALUES)
		ft_putstr_fd(ERR_MSG_SP_COLOR_VALUES, 2);
}
