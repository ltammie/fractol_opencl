#include "../includes/fractol.h"

static	int		close_menu(int key, t_mlx *data)
{
	if (key == H)
		help_menu(key, data);
	return (0);
}

int				redraw(int key, t_mlx *data)
{
	if (key == SPACE)
	{
		init_view(&data->v, data->fractal_type);
		data->max_iter = 100;
		mlx_clear_window(data->mlx, data->win);
		draw_image(data);
	}
	return (0);
}

int				refresh(int key, t_mlx *data)
{
	if (key == R)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_do_sync(data->mlx);
		draw_image(data);
	}
	return (0);
}

void			close_fractol(t_mlx *data)
{
	if (data->v.music_status == 1)
		play_music(data);
	cl_free(&data->cl);
	free(data->res);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	(void)data;
	exit(0);
}

int				help_menu(int key, t_mlx *data)
{
	if (key == H)
	{
		if (data->help_status == 0)
		{
			if (!(data->help = mlx_new_window(data->mlx,
					HELP_WIDTH, HELP_HEIGHT, "Help")))
				error(MLX_HELP_WINDOW_CREATE_ERROR);
			data->help_status = 1;
			show_menu(data);
			mlx_hook(data->help, 2, 0, close_menu, data);
		}
		else
		{
			mlx_destroy_window(data->mlx, data->help);
			data->help_status = 0;
		}
	}
	return (0);
}
