/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:03 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/15 17:28:54 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void draw_colored_pixels(t_rt *rt, int color)
{
    int x, y;

    for (y = 10; y < 20; y++)
    {
        for (x = 10; x < 20; x++)
            set_pixel_color(&rt->mlx.img, x, y, color);
    }

    for (y = 30; y < 40; y++)
    {
        for (x = 10; x < 20; x++)
            set_pixel_color(&rt->mlx.img, x, y, color);
    }

    for (y = 50; y < 60; y++)
    {
        for (x = 10; x < 20; x++)
            set_pixel_color(&rt->mlx.img, x, y, color);
    }

    for (y = 70; y < 80; y++)
    {
        for (x = 10; x < 20; x++)
            set_pixel_color(&rt->mlx.img, x, y, color);
    }

    for (y = 90; y < 100; y++)
    {
        for (x = 10; x < 20; x++)
            set_pixel_color(&rt->mlx.img, x, y, color);
    }
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

	fill_image(rt, YELLOW); // just for testing to see if image shown in window
	draw_colored_pixels(rt, BLUE); // just for testing to see if image shown in window

	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.img.img, 0, 0);

	start_event_loop(rt);
}
