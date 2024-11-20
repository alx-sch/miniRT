/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:03 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/20 23:09:32 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
Function to create a simple scene with a three sphere.
Takes a pointer to t_rt, which includes both mlx and scene.
*/
void	create_simple_scene(t_rt *rt)
{
	t_list		*obj_node;
	t_obj_data	*sphere_data;

	// Set up ambient light
	rt->scene.ambi_light.ratio = 0.1;  // Low ambient light
	rt->scene.ambi_light.color.r = 255;
	rt->scene.ambi_light.color.g = 255;
	rt->scene.ambi_light.color.b = 255;

	// Set up the light source
	rt->scene.light.position.x = 0.0;
	rt->scene.light.position.y = 10.0;
	rt->scene.light.position.z = 0.0;
	rt->scene.light.ratio = 1.0;  // Full brightness

	// Set up the camera
	rt->scene.cam.position.x = 1.0;
	rt->scene.cam.position.y = 1.0;
	rt->scene.cam.position.z = -5.0;  // Camera placed along the negative Z-axis
	rt->scene.cam.orientation.x = 0.0;
	rt->scene.cam.orientation.y = 0.0;
	rt->scene.cam.orientation.z = 1.0;  // Looking down the Z-axis
	rt->scene.cam.fov = 90.0;  // Field of view

	// Set up a single sphere object (front)
	sphere_data = malloc(sizeof(t_obj_data));
    if (!sphere_data)
        return;

	// Create the sphere data
	sphere_data->sp.object_type = SPHERE;
	sphere_data->sp.center.x = 0.0;
	sphere_data->sp.center.y = 0.0;
	sphere_data->sp.center.z = 0.0;
	sphere_data->sp.radius = 2.0;  // Radius of the sphere
	sphere_data->sp.color.r = 255;
	sphere_data->sp.color.g = 0;
	sphere_data->sp.color.b = 0;  // Red sphere


	// Create a new list node with the sphere data
	obj_node = ft_lstnew(sphere_data);
	if (!obj_node)
	{
		free(sphere_data);  // Clean up if node creation fails
		return;  // Handle memory allocation failure
	}

	ft_lstadd_front(&rt->scene.objs, obj_node);

	// Set up the second sphere object (blue, behind the red one)
    sphere_data = malloc(sizeof(t_obj_data));
    if (!sphere_data)
        return;

    sphere_data->sp.object_type = SPHERE;
    sphere_data->sp.center.x = 1.5;
    sphere_data->sp.center.y = 1.5;
    sphere_data->sp.center.z = 1.5;  // Positioned behind the red sphere
    sphere_data->sp.radius = 2.75;  // Radius of the sphere
    sphere_data->sp.color.r = 0;
    sphere_data->sp.color.g = 0;
    sphere_data->sp.color.b = 255;  // Blue sphere

    obj_node = ft_lstnew(sphere_data);
    if (!obj_node)
    {
        free(sphere_data);  // Clean up if node creation fails
        return;  // Handle memory allocation failure
    }

    ft_lstadd_front(&rt->scene.objs, obj_node);

	// Set up the second sphere object (blue, behind the red one)
    sphere_data = malloc(sizeof(t_obj_data));
    if (!sphere_data)
        return;

    sphere_data->sp.object_type = SPHERE;
    sphere_data->sp.center.x = 0.5;
    sphere_data->sp.center.y = 1;
    sphere_data->sp.center.z = -0.5;  // Positioned behind the red sphere
    sphere_data->sp.radius = 1.5;  // Radius of the sphere
    sphere_data->sp.color.r = 0;
    sphere_data->sp.color.g = 255;
    sphere_data->sp.color.b = 0;  // Blue sphere

    obj_node = ft_lstnew(sphere_data);
    if (!obj_node)
    {
        free(sphere_data);  // Clean up if node creation fails
        return;  // Handle memory allocation failure
    }

    ft_lstadd_front(&rt->scene.objs, obj_node);
}

int	main(void)
{
	t_rt	*rt;

	rt = malloc(sizeof(t_rt));
	if (!rt)
		cleanup_error_exit(ERR_MALLOC, NULL);

	//check args / .rt file
	//populate scene info into data struct (parse file)

	init_mlx(rt);
	create_simple_scene(rt);

	render_scene(rt, YELLOW); // render a simple scene without shadows, lighting considerations etc.

	//fill_image(rt, RED); // just for testing to see if image shown in window

	mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
		rt->mlx.img.img_ptr, 0, 0);

	start_event_loop(rt);
}
