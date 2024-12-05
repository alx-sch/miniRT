/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:22:32 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/05 13:46:07 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Allocates memory for an n amount of nonunique elements (sphere, plane and
cylinder). Returns 0 upon success, or returns 1 if mem allocation failed.*/
int	allocate_nonunique_elements(t_tmp_scene *scene)
{
	int	i;

	i = 0;
	scene->plane = malloc(sizeof(t_plane) * scene->tot_pl);
	if (!scene->plane)
		return (1);
	while (i < scene->tot_pl)
		init_plane(&scene->plane[i++]);
	i = 0;
	scene->sphere = malloc(sizeof(t_sphere) * scene->tot_sp + 1);
	if (!scene->sphere)
		return (1);
	while (i < scene->tot_sp)
		init_sphere(&scene->sphere[i++]);
	i = 0;
	scene->cyl = malloc(sizeof(t_cylinder) * scene->tot_cy + 1);
	if (!scene->cyl)
		return (1);
	while (i < scene->tot_cy)
		init_cylinder(&scene->cyl[i++]);
	return (0);
}

/*Initializes all values of the t_sp struct to 0.*/
void	init_sphere(t_sphere *sp)
{
	sp->object_type = SPHERE;
	sp->center.x = 0;
	sp->center.y = 0;
	sp->center.z = 0;
	sp->radius = 0;
	sp->color.r = 0;
	sp->color.g = 0;
	sp->color.b = 0;
	sp->ixd.a = 0;
	sp->ixd.axis_dot_oc = 0;
	sp->ixd.b = 0;
	sp->ixd.c = 0;
	sp->ixd.difference.x = 0;
	sp->ixd.difference.y = 0;
	sp->ixd.difference.z = 0;
	sp->ixd.discriminant = 0;
	sp->ixd.oc.x = 0;
	sp->ixd.oc.y = 0;
	sp->ixd.oc.z = 0;
}

/*Initializes all values of the t_pl struct to 0.*/
void	init_plane(t_plane *pl)
{
	pl->object_type = PLANE;
	pl->point_in_plane.x = 0;
	pl->point_in_plane.y = 0;
	pl->point_in_plane.z = 0;
	pl->normal.x = 0;
	pl->normal.y = 0;
	pl->normal.z = 0;
	pl->color.r = 0;
	pl->color.g = 0;
	pl->color.b = 0;
	pl->ixd.a = 0;
	pl->ixd.axis_dot_oc = 0;
	pl->ixd.b = 0;
	pl->ixd.c = 0;
	pl->ixd.difference.x = 0;
	pl->ixd.difference.y = 0;
	pl->ixd.difference.z = 0;
	pl->ixd.discriminant = 0;
	pl->ixd.oc.x = 0;
	pl->ixd.oc.y = 0;
	pl->ixd.oc.z = 0;
}

static void	init_vec3(t_vec3 coords)
{
	coords.x = 0;
	coords.y = 0;
	coords.z = 0;
}

/*Initializes all values of the t_cy struct to 0.*/
void	init_cylinder(t_cylinder *cy)
{
	cy->object_type = CYLINDER;
	init_vec3(cy->center);
	init_vec3(cy->orientation);
	cy->radius = 0;
	cy->radius_sqrd = 0;
	cy->height = 0;
	init_vec3(cy->cap_top_center);
	init_vec3(cy->cap_bottom_center);
	init_vec3(cy->cap_top_normal);
	init_vec3(cy->cap_bottom_normal);
	cy->color.r = 0;
	cy->color.g = 0;
	cy->color.b = 0;
	cy->ixd.a = 0;
	cy->ixd.axis_dot_oc = 0;
	cy->ixd.b = 0;
	cy->ixd.c = 0;
	cy->ixd.difference.x = 0;
	cy->ixd.difference.y = 0;
	cy->ixd.difference.z = 0;
	cy->ixd.discriminant = 0;
	cy->ixd.oc.x = 0;
	cy->ixd.oc.y = 0;
	cy->ixd.oc.z = 0;
}
