#include "includes/fractol.h"

static	void check_argv(int type)
{
	if (type != 1 && type != 2 && type != 3 && type != 4  && type != 5)
		error(1);
}

static int	mouse_button_release(int button, int x, int y, t_mlx *data)
{
	if (button == LEFT_MB || button == RIGHT_MB)
		if (x && y)
			data->view.b = 0;
	return (0);
}

static int	mouse_button_press(int button, int x, int y, t_mlx *data)
{
	if (button == LEFT_MB || button == RIGHT_MB)
	{
		data->view.b = 1;
		data->view.pressed_button = button;
		data->view.zoom_x = x;
		data->view.zoom_y = y;
		zoom(button, data, x, y);
	}
	return (0);
}

static int no_events(t_mlx *data)
{
	if (data->view.b == 1)
		zoom(data->view.pressed_button, data, data->view.zoom_x, data->view.zoom_y);
	return (0);
}

static int	key_press(int key, t_mlx *data)
{
	if (key == W || key == A || key == S || key == D)
		arrow_move(key, data);
	if (key == Q || key == E)
		max_iter_change(key, data);
	if (key == R)
		refresh(key, data);
	if (key == H)
		help_menu(key, data);
	if (key == P)
	{
		for (int i = 0; i < HEIGHT ; ++i)
		{
			for (int j = 0; j < WIDTH; ++j)
			{
				write(open("screenshot.jpeg",O_WRONLY), &data->img.img_data[i * WIDTH + j], 4);
			}
		}

	}
	if (key == M)
		data->view.julia_change_mod = (data->view.julia_change_mod == 1) ? 0 : 1;
	if (key == SPACE)
		redraw(key, data);
	if (key == ONE || key == TWO || key == THREE || key == FOUR)
		change_color(key,data);
	if (key == ESC)
		close_fractol(data);
	return (0);
}

int			main(int argc, char **argv)
{
	t_mlx *data;

	if (argc != 2)
		error(1);
	check_argv(ft_atoi(argv[1]));
	data = init_data(ft_atoi(argv[1]));
	data->cl.kernel_source = get_kernel_source(&data->cl, data->cl_source);
	cl_init(&data->cl);
	draw_image(data);
	mlx_hook(data->win, 2, 0, key_press, data);
	mlx_hook(data->win, 4, 0, mouse_button_press, data);
	mlx_hook(data->win, 5, 0, mouse_button_release, data);
	mlx_hook(data->win, 6, 0, change_julia, data);
	mlx_loop_hook(data->mlx, no_events, data);
	mlx_loop(data->mlx);
	return (0);
}
