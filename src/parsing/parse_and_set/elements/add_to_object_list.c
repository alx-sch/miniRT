/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_object_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:17:16 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/06 15:55:53 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Adds an object to the linked list of objects.*/
int	add_to_object_list(t_scene **scene, t_obj_data **obj_data)
{
	t_list	*obj_node;

	obj_node = ft_lstnew(*obj_data);
	if (!obj_node)
	{
		free(obj_data);
		return (ERR_MEM_ALLOC);
	}
	ft_lstadd_back(&(*scene)->objs, obj_node);
	return (0);
}
