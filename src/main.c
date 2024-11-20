/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:03 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/19 15:54:19 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


int	main(void)
{
	t_rt	*rt;

	rt = malloc(sizeof(t_rt));
	if (!rt)
		cleanup_error_exit(ERR_MALLOC, NULL);

	//check args / .rt file
	//populate scene info into data struct (parse file)

	init_mlx(rt);

	fill_image(rt, RED); // just for testing to see if image shown in window
	draw_colored_pixels(rt, YELLOW); // just for testing to see if image shown in window

	mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
		rt->mlx.img.img_ptr, 0, 0);

	start_event_loop(rt);
}
