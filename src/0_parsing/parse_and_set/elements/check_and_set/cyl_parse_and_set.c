/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_parse_and_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:53:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/09 11:28:01 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Stores various attributes of the cylinder in the linked list of objects.*/
static void	set_special_attributes_cylinder(t_scene **scene, \
t_obj_data **obj_data)
{
	(*obj_data)->cy.cap_top_center = vec3_add((*obj_data)->cy.center, \
	vec3_mult((*obj_data)->cy.orientation, (*obj_data)->cy.height / 2.0));
	(*obj_data)->cy.cap_bottom_center = vec3_sub((*obj_data)->cy.center, \
	vec3_mult((*obj_data)->cy.orientation, (*obj_data)->cy.height / 2.0));
	(*obj_data)->cy.cap_top_normal = (*obj_data)->cy.orientation;
	(*obj_data)->cy.cap_bottom_normal = vec3_mult((*obj_data)->cy.orientation, \
	-1.0);
	(*obj_data)->cy.ixd.oc = vec3_sub((*scene)->cam.pos, \
	(*obj_data)->cy.center);
	(*obj_data)->cy.ixd.axis_dot_oc = vec3_dot((*obj_data)->cy.ixd.oc, \
	(*obj_data)->cy.orientation);
	(*obj_data)->cy.ixd.c = vec3_dot((*obj_data)->cy.ixd.oc, \
		(*obj_data)->cy.ixd.oc) - ((*obj_data)->cy.ixd.axis_dot_oc * \
		(*obj_data)->cy.ixd.axis_dot_oc) \
		- (*obj_data)->cy.radius_sqrd;
}

/*Stores the radius and height of the cylinder in the linked list of objects.*/
static void	set_r_and_h(t_obj_data **obj_data, char *diameter, \
char *height)
{
	(*obj_data)->cy.radius = (ft_atod(diameter) / 2);
	(*obj_data)->cy.radius_sqrd = \
	(*obj_data)->cy.radius * (*obj_data)->cy.radius;
	(*obj_data)->cy.height = ft_atod(height);
}

/*Stores all the data of the current cylinder in the linked list of objects.*/
int	set_cylinder(t_scene *scene)
{
	t_obj_data	*obj_data;
	char		**rgb;

	obj_data = malloc(sizeof(t_obj_data));
	if (!obj_data)
		return (ERR_MEM_ALLOC);
	obj_data->sp.object_type = CYLINDER;
	if (set_coordinates(scene->pars.elem_data[1], &obj_data->cy.center.x, \
		&obj_data->cy.center.y, &obj_data->cy.center.z) != 0)
		return (ERR_MEM_ALLOC);
	if (set_orientation_vector(scene->pars.elem_data[2], \
		&obj_data->cy.orientation.x, &obj_data->cy.orientation.y, \
		&obj_data->cy.orientation.z))
		return (ERR_MEM_ALLOC);
	set_r_and_h(&obj_data, scene->pars.elem_data[3], scene->pars.elem_data[4]);
	rgb = ft_split(scene->pars.elem_data[5], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &obj_data->cy.color.r, &obj_data->cy.color.g, \
	&obj_data->cy.color.b);
	set_special_attributes_cylinder(&scene, &obj_data);
	if (add_to_object_list(&scene, &obj_data) != 0)
		return (ERR_MEM_ALLOC);
	return (0);
}

/*Parses a cylinder object.
1. Checks if there's a correct amount of fields (6).
2. Checks if the coordinates are valid.
3. Checks if the orientation vector is valid.
4. Checks if the diameter is valid.
5. Checks if the height is valid.
6. Checks if the color values are valid.
Also keeps track of the count, ultimately storing the total count (how
many occurences of the object), to be able to allocate memory correctly
later on.
Returns 0 upon success, and an error code upon error.*/
int	parse_cylinder(t_scene *scene)
{
	char	**rgb;

	scene->tot_cyl++;
	if (!correct_amt_of_fields(scene->pars.elem_data, 6))
		return (ERR_CY_FIELDS);
	if (check_coordinates(scene->pars.elem_data[1], \
	&scene->pars.error_code, ERR_CY_COOR_FIELDS) != 0)
		return (scene->pars.error_code);
	if (check_orientation_vector(scene->pars.elem_data[2], \
	&scene->pars.error_code, ERR_CY_VECTOR_FIELDS) != 0)
		return (scene->pars.error_code);
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[3]))
		return (ERR_CY_DM);
	if (!only_numbers_and_dec_pt(scene->pars.elem_data[4]))
		return (ERR_CY_HEIGHT);
	rgb = ft_split(scene->pars.elem_data[5], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	if (check_color(rgb, &scene->pars.error_code, ERR_CY_COLOR_FIELDS) != 0)
	{
		ft_freearray(rgb);
		return (scene->pars.error_code);
	}
	ft_freearray(rgb);
	return (set_cylinder(scene));
}
