#include "includes/fractol.h"

int 	redraw(int key, t_mlx *data)
{
	if (key == SPACE)
	{
		init_view(&data->view);
		mlx_clear_window(data->mlx, data->win);
		draw_image(data);
	}
	return (0);
}

int 	refresh(int key, t_mlx *data)
{
	if (key == R)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_do_sync(data->mlx);
		draw_image(data);
	}
	return (0);
}

void	close_fractol(t_mlx *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	(void)data;
	exit(0);
}
