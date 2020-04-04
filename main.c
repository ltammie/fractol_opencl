#include "includes/fractol.h"

static	void check_argv(char *fr)
{
	if (ft_strcmp(fr, "Mandelbrot") != 0 && ft_strcmp(fr, "Julia") != 0)
		error(1);
}

int		key_press(int key, t_mlx *data)
{
	if (key == ESC)
		close_fractol(data);
	return (0);
}

int main(int argc, char **argv)
{
	t_mlx *data;

	if (argc != 2)
		error(1);
	check_argv(argv[1]);
	data = init_data(argv[1]);
	printf("fractal type: %s\n", data->fractal_type);
	draw_image(data);
	mlx_hook(data->win, 2, (1L << 0), key_press, data);
	mlx_loop(data->mlx);
	return (0);
}
