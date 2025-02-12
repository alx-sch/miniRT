/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_parse_and_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:53:10 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/12 23:57:24 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Stores various attributes of the cylinder in the linked list of objects.*/
static void	set_special_attributes_cylinder(t_scene **scene, t_obj **obj)
{
	(*obj)->cy.cap_top_center = vec3_add((*obj)->cy.center, \
	vec3_mult((*obj)->cy.orientation, (*obj)->cy.height / 2.0));
	(*obj)->cy.cap_bottom_center = vec3_sub((*obj)->cy.center, \
	vec3_mult((*obj)->cy.orientation, (*obj)->cy.height / 2.0));
	(*obj)->cy.cap_top_normal = (*obj)->cy.orientation;
	(*obj)->cy.cap_bottom_normal = vec3_mult((*obj)->cy.orientation, -1.0);
	(*obj)->cy.ixd.oc = vec3_sub((*scene)->cam.pos, (*obj)->cy.center);
	(*obj)->cy.ixd.axis_dot_oc = vec3_dot((*obj)->cy.ixd.oc, \
	(*obj)->cy.orientation);
	(*obj)->cy.ixd.c = vec3_dot((*obj)->cy.ixd.oc, \
		(*obj)->cy.ixd.oc) - ((*obj)->cy.ixd.axis_dot_oc * \
		(*obj)->cy.ixd.axis_dot_oc) - (*obj)->cy.radius_sqrd;
	(*obj)->cy.ixd.cap_hit = 0;
	(*obj)->cy.hex_color = color_to_hex((*obj)->cy.color);
	(*obj)->cy.ixd.dot_to_top = vec3_dot(vec3_sub(
				(*obj)->cy.cap_top_center, (*scene)->cam.pos),
			(*obj)->cy.cap_top_normal);
	(*obj)->cy.ixd.dot_to_bottom = vec3_dot(vec3_sub(
				(*obj)->cy.cap_bottom_center, (*scene)->cam.pos),
			(*obj)->cy.cap_bottom_normal);
}

/*Stores the radius and height of the cylinder in the linked list of objects.*/
static void	set_r_and_h(t_obj **obj, char *diameter, char *height)
{
	(*obj)->cy.radius = (ft_atod(diameter) / 2);
	(*obj)->cy.radius_sqrd = (*obj)->cy.radius * (*obj)->cy.radius;
	(*obj)->cy.height = ft_atod(height);
}

/*Stores all the data of the current cylinder in the linked list of objects.*/
int	set_cylinder(t_scene *scene)
{
	t_obj	*obj;
	char	**rgb;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (ERR_MEM_ALLOC);
	obj->sp.object_type = CYLINDER;
	if (set_coordinates(scene->pars.elem_data[1], &obj->cy.center.x, \
		&obj->cy.center.y, &obj->cy.center.z) != 0)
		return (ERR_MEM_ALLOC);
	if (set_orientation_vector(scene->pars.elem_data[2], \
		&obj->cy.orientation.x, &obj->cy.orientation.y, &obj->cy.orientation.z))
		return (ERR_MEM_ALLOC);
	set_r_and_h(&obj, scene->pars.elem_data[3], scene->pars.elem_data[4]);
	rgb = ft_split(scene->pars.elem_data[5], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &obj->cy.color.r, &obj->cy.color.g, &obj->cy.color.b);
	set_special_attributes_cylinder(&scene, &obj);
	obj->cy.hit = 0;
	if (add_to_object_list(&scene, &obj) != 0)
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
