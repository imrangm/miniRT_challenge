#include "./includes/minirt.h"

int	key(int keycode, t_data *scene_data)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(scene_data->mlx.mlx_ptr, scene_data->mlx.win_ptr);
		free_scene_data(scene_data);
		exit (0);
	}
	return (0);
}

int	win_close(t_data *scene_data)
{
	mlx_destroy_window(scene_data->mlx.mlx_ptr, scene_data->mlx.win_ptr);
	free_scene_data(scene_data);
	exit (0);
}

void	setup_mlx(t_data *scene_data)
{
	scene_data->mlx.mlx_ptr = malloc(sizeof(*scene_data->mlx.mlx_ptr));
	scene_data->mlx.mlx_ptr = mlx_init();
	scene_data->img.img_ptr = mlx_new_image(scene_data->mlx.mlx_ptr,
			WIDTH, HEIGHT);
	scene_data->img.data = (unsigned char *) mlx_get_data_addr
		(scene_data->img.img_ptr, &(scene_data->img.bits_per_pixel),
			&(scene_data->img.size_line), &(scene_data->img.endian));
	scene_data->mlx.win_ptr = mlx_new_window(scene_data->mlx.mlx_ptr,
			WIDTH, HEIGHT, "minirt");
}

void	init_scene_data(t_data *scene_data)
{
	scene_data->amb_set = 0;
	scene_data->wrld.shapes = NULL;
	scene_data->camera2.init = 0;
}

void	write_pixel1(double w, double h, t_color color, t_data *scene_data)
{
	int				rr;
	int				gg;
	int				bb;
	int				color_code;
	unsigned char	*dst;

	rr = color.r * 255;
	gg = color.g * 255;
	bb = color.b * 255;
	color_code = rr << 16 | gg << 8 | bb;
	dst = scene_data->img.data + (int)(h * scene_data->img.size_line
			+ w * (scene_data->img.bits_per_pixel / 8));
	*(unsigned int *) dst = color_code;
}

int	main(int argc, char **argv)
{
	t_data		scene_data;

	if (argc != 2)
		print_error_msg_and_exit("NOT ENOUGH ARGUMENTS", &scene_data);
	init_scene_data(&scene_data);
	if (parse_scene(argv[1], &scene_data))
	{
		setup_mlx(&scene_data);
		default_world(&scene_data);
		render(scene_data.camera2, scene_data.wrld, &scene_data);
		mlx_put_image_to_window(scene_data.mlx.mlx_ptr, scene_data.mlx.win_ptr,
			scene_data.img.img_ptr, 0, 0);
		mlx_key_hook(scene_data.mlx.win_ptr, &key, &scene_data);
		mlx_hook(scene_data.mlx.win_ptr, ON_DESTROY, 0,
			win_close, &scene_data);
		mlx_loop(scene_data.mlx.mlx_ptr);
		// free(scene_data.mlx.mlx_ptr);
		// free_scene_data(&scene_data);
		// exit (0);
	}
	else
		print_error_msg_and_exit(scene_data.error.message, &scene_data);
	return (0);
}
