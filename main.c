#include "includes/fractol.h"

static	void check_argv(char *fr)
{
	if (ft_strcmp(fr, "Mandelbrot") != 0 && ft_strcmp(fr, "Julia") != 0)
		error(1);
}

int		key_press(int key, t_mlx *data)
{
	if (key == MIN || key == PLUS)
		zoom(key, data);
	if (key == W || key == A || key == S || key == D)
		arrow_move(key, data);
	if (key == Q || key == E)
		max_iter_change(key, data);
	if (key == R)
		refresh(key, data);
	if (key == SPACE)
		redraw(key, data);
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
	printf("%s\n", data->fractal_type);
	data->cl.kernel_source = get_kernel_source(&data->cl, data->fractal_type);
	draw_image(data);
	mlx_hook(data->win, 2, (1L << 0), key_press, data);
//	mlx_hook(data->win, 6, (1L<<1), mouse_move, data);
	mlx_loop(data->mlx);
	return (0);
}
