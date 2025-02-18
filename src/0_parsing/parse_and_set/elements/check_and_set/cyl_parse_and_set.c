/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_parse_and_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:53:10 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/18 22:00:13 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Stores various attributes of the cylinder in the linked list of objects.*/
static void	set_special_attributes_cylinder(t_obj **obj)
{
	(*obj)->x.cy.cap_top_normal = (*obj)->x.cy.orientation;
	(*obj)->x.cy.cap_bottom_normal = vec3_mult((*obj)->x.cy.orientation, -1.0);
	(*obj)->x.cy.cap_top_center = vec3_add((*obj)->x.cy.center, \
	vec3_mult((*obj)->x.cy.cap_top_normal, (*obj)->x.cy.height / 2.0));
	(*obj)->x.cy.cap_bottom_center = vec3_add((*obj)->x.cy.center, \
	vec3_mult((*obj)->x.cy.cap_bottom_normal, (*obj)->x.cy.height / 2.0));
}

/*Stores the radius and height of the cylinder in the linked list of objects.*/
static void	set_r_and_h(t_obj **obj, char *diameter, char *height)
{
	(*obj)->x.cy.radius = (ft_atod(diameter) / 2);
	(*obj)->x.cy.radius_sqrd = (*obj)->x.cy.radius * (*obj)->x.cy.radius;
	(*obj)->x.cy.height = ft_atod(height);
	(*obj)->x.cy.height_half = (*obj)->x.cy.height / 2.0;
}

/*Stores all the data of the current cylinder in the linked list of objects.*/
int	set_cylinder(t_scene *scene)
{
	t_obj	*obj;
	char	**rgb;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (ERR_MEM_ALLOC);
	obj->object_type = CYLINDER;
	if (set_coordinates(scene->pars.elem_data[1], &obj->x.cy.center.x, \
		&obj->x.cy.center.y, &obj->x.cy.center.z) != 0)
		return (ERR_MEM_ALLOC);
	if (set_orientation_vector(scene->pars.elem_data[2], \
		&obj->x.cy.orientation.x, &obj->x.cy.orientation.y, \
		&obj->x.cy.orientation.z))
		return (ERR_MEM_ALLOC);
	set_r_and_h(&obj, scene->pars.elem_data[3], scene->pars.elem_data[4]);
	rgb = ft_split(scene->pars.elem_data[5], ',');
	if (!rgb)
		return (ERR_MEM_ALLOC);
	set_color(rgb, &obj->color.r, &obj->color.g, &obj->color.b);
	set_special_attributes_cylinder(&obj);
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

	scene->pars.tot_cyl++;
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
