#include "includes/fractol.h"

void			color_fractal(t_mlx *data)
{
	for (int i = 0; i < HEIGHT ; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (data->view.color_type == 1)
				data->img.img_data[i * WIDTH + j] = basic_one(data->result[i * WIDTH + j], data->max_iter);
			if (data->view.color_type == 2)
				data->img.img_data[i * WIDTH + j] = zerg(data->result[i * WIDTH + j], data->max_iter);
			if (data->view.color_type == 3)
				data->img.img_data[i * WIDTH + j] = sin_coloring(data->result[i * WIDTH + j]);
			if (data->view.color_type == 4)
				data->img.img_data[i * WIDTH + j] = black_hole(data->result[i * WIDTH + j], data->max_iter);
		}
	}
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

//fix
int				sin_coloring(int x)
{
	t_rgb color;

	color.t_rgba.r = sin(0.016 * x + 30) * 200 + 55;
	color.t_rgba.g = sin(0.013 * x + 15) * 200 + 55;
	color.t_rgba.b = sin(0.01 * x + 10) * 200 + 55;
	color.t_rgba.a = 0;
	return (color.c);
}

int				zerg(int i, int max)
{
	t_rgb color;

	if (i == max)
		return (BLACK);
	color.t_rgba.r = i * 6 % 255;
	color.t_rgba.g = 0;
	color.t_rgba.b = i * 6 % 255;
	color.t_rgba.a = 0;
	return (color.c);
}

int				basic_one(float i, int max)
{
	t_rgb color;
	float k;

	if (i == max)
		return (BLACK);
	k = i / (float)max;
	color.t_rgba.r = (int)(9 * (1 - k) * (k * k * k) * 255);
	color.t_rgba.g = (int)(15 * ((1 - k) * (1 - k)) * (k * k) * 255);
	color.t_rgba.b = (int)(8.5 * ((1 - k) * (1 - k) * (1 - k)) * k * 255);
	color.t_rgba.a = 0;
	return (color.c);
}

int				black_hole(int i, int max)
{
	t_rgb color;

	if (i == max)
		return (BLACK);
	color.t_rgba.r = i * 15 % 255;
	color.t_rgba.g = i * 7 % 255;
	color.t_rgba.b = 0;
	color.t_rgba.a = 0;
	return (color.c);
}
