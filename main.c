#include "includes/fractol.h"

static	void check_argv(char *fr)
{
	if (ft_strcmp(fr, "Mandelbrot") != 0 && ft_strcmp(fr, "Julia") != 0)
		error(1);
}

static int		mouse_button_press(int button, int x, int y, t_mlx *data)
{
	if (x)
		;
	if (y)
		;
	if (button == LEFT_MB || button == RIGHT_MB)
		zoom(button, data);
	return (0);
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
	data->cl.kernel_source = get_kernel_source(&data->cl, data->fractal_type);
	draw_image(data);
	mlx_hook(data->win, 2, (1L << 0), key_press, data);
	mlx_hook(data->win, 4, (1L << 2), mouse_button_press, data); // 4 for press, 5 for release, 6 for movement
	mlx_loop(data->mlx);
	return (0);
}
