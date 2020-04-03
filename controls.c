#include "includes/fractol.h"

int		zoom(int key, t_mlx *data)
{
	if (key == MIN)
	{
		if (data->view.minValue >= -2 && data->view.maxValue >= 0)
		{
			data->view.minValue -= 0.01f;
			data->view.minValue -= 0.01f;
		}
	}
	if (key == PLUS)
	{
		if (data->view.minValue <= 0 && data->view.maxValue <= 1)
		{
			data->view.minValue += 0.01f;
			data->view.minValue += 0.01f;
		}
	}
	mlx_clear_window(data->mlx, data->win);
	draw_image(data);
	return (0);
}

void	close_fractol(t_mlx *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	(void)data;
	exit(0);
}
