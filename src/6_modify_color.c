/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_ray_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:23:12 by nholbroo          #+#    #+#             */
/*   Updated: 2025/01/14 15:54:48 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_ray_in_shadow(t_vec3 ray_dir, t_rt *rt, t_ixr *ixr)
{
	t_list		*current_obj;
	t_obj_data	*obj_data;

	current_obj = rt->scene.objs;
	while (current_obj != NULL)
	{
		obj_data = (t_obj_data *)current_obj->content;
		if (obj_data->pl.object_type == PLANE)
		{
			if (shadow_check_plane_intersection(rt, ray_dir, obj_data, &ixr))
				return (1);
		}
		else if (obj_data->sp.object_type == SPHERE)
		{
			if (shadow_check_sphere_intersection(rt, ray_dir, obj_data, &ixr))
				return (1);
		}
		else if (obj_data->cy.object_type == CYLINDER)
		{
			if (shadow_check_cyl_intersection(rt, ray_dir, obj_data, &ixr))
				return (1);
		}
		current_obj = current_obj->next;
	}
	return (0);
}

void	modify_color(t_vec3 ray_dir, t_rt *rt, t_ixr *ixr)
{
	if (is_ray_in_shadow(ray_dir, rt, ixr))
		ixr->ixn_color = 0;
}
