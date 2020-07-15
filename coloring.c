#include "includes/fractol.h"

void			color_fractal(t_mlx *data)
{
	int i;
	int j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (data->view.color_type == 1)
				data->img.img_data[i * WIDTH + j] = basic_one(data->result[i * WIDTH + j], (float)data->max_iter);
			if (data->view.color_type == 2)
				data->img.img_data[i * WIDTH + j] = zerg(data->result[i * WIDTH + j], (float)data->max_iter);
			if (data->view.color_type == 3)
				data->img.img_data[i * WIDTH + j] = black_hole(data->result[i * WIDTH + j], (float)data->max_iter);
			if (data->view.color_type == 4)
				data->img.img_data[i * WIDTH + j] = mix(data->result[i * WIDTH + j], (float)data->max_iter);
			j++;
		}
		i++;
	}
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

int				zerg(float x, float max)
{
	float k;
	t_rgb color;

	if (x == max)
		return (BLACK);
	k = (x / max);
	color = hsv_to_rgb(320, 0.8f, 1 * k);

	return ((int)color.c);
}

int				basic_one(float i, float max)
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

int				black_hole(float i, float max)
{
	float k;
	t_rgb color;

	if (i == max)
		return (WHITE);
	k = (i / max);
	color = hsv_to_rgb(15, 1, 1 * k);
	return (color.c);

}

int				mix(float i, float max)
{
	t_rgb color;
	float k;

	if (i == max)
		return (BLACK);
	k = i / (float)max;
	color.t_rgba.r = (int)(6.4 * ((1 - k) * (1 - k) * (1 - k)) * k * 255);
	color.t_rgba.g = (int)(9.2 * ((1 - k) * (1 - k)) * (k * k) * 255);
	color.t_rgba.b = (int)(12.7 * (1 - k) * (k * k * k) * 255);
	color.t_rgba.a = 0;
	return (color.c);
}
