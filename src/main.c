/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:13:03 by aschenk           #+#    #+#             */
/*   Updated: 2024/12/06 16:04:01 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_rt	*rt;

	rt = ft_calloc(1, sizeof(t_rt));
	if (!rt)
		cleanup_error_exit(ERR_MALLOC, NULL);
	parse_and_set_objects(rt, argc, argv);
	init_mlx(rt);
	render_scene(rt, BLACK); // render a simple scene without shadows, lighting considerations etc.
	// fill_image(rt, RED); // just for testing to see if image shown in window
	mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
		rt->mlx.img.img_ptr, 0, 0);
	start_event_loop(rt);
	cleanup(&rt);
}
