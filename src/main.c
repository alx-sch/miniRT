#include "main.h"

/**
The main function initializes and runs the `miniRT` ray tracing program.

1.	Allocates and initializes memory for the scene structure (`t_rt`).
2.	Parses the input arguments and sets up scene objects from the provided
	`.rt` file.
3.	Initializes the graphical window and sets up the rendering environment
	using MLX.
4.	Renders the scene by tracing rays, computing shading, and applying lighting.
5.	Displays the rendered image in the window.
6.	Starts the event loop to handle user input and window events.
7.	Cleans up resources and exits the program.

 @return	`0` upon successful execution. If an error occurs, the program exits
 			with an appropriate error code (see `parsing.h` for error codes set
			during parsing).
*/
int	main(int argc, char **argv)
{
	t_rt	*rt;

	rt = ft_calloc(1, sizeof(t_rt));
	if (!rt)
		cleanup_error_exit(ERR_MALLOC, NULL);
	parse_and_set_objects(rt, argc, argv);
	init_mlx(rt);
	render_scene(rt);
	mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
		rt->mlx.img.img_ptr, 0, 0);
	start_event_loop(rt);
	cleanup(&rt);
	return (0);
}
