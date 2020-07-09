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
				data->img.img_data[i * WIDTH + j] = sin_coloring(data->result[i * WIDTH + j], data->max_iter);
			if (data->view.color_type == 4)
				data->img.img_data[i * WIDTH + j] = black_hole(data->result[i * WIDTH + j], data->max_iter);
		}
	}
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

int				sin_coloring(float x, int max)
{
	t_rgb color;

	if (x == max)
		return (RED);
	color.t_rgba.r = sin(0.016 * x + 30) * 200 + 55;
	color.t_rgba.g = sin(0.013 * x + 15) * 200 + 55;
	color.t_rgba.b = sin(0.01 * x + 10) * 200 + 55;
	color.t_rgba.a = 0;
	return (color.c);
}

int				zerg(float x, int max)
{
	t_rgb color;

	if (x == max)
		return (BLACK);
	color.t_rgba.r = sin(0.03 * x + 25) * 200 + 55;
	color.t_rgba.g = 0;
	color.t_rgba.b = sin(0.05 * x + 50) * 200 + 55;
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

int				black_hole(float i, int max)
{
	float k;
	t_rgb color;

	if (i == max)
		return (WHITE);
	k = (i / max);
//	if (i > 70)
//		color = new_rgb_color(0, 0, (int)(255.0 * k));
//	else
//		color = new_rgb_color((int)(255.0 * k), 0, 0);
	color = hsv_to_rgb(95 + 10 * k, 0.6f, 1.0f);
//	printf("%f\n", k);
//	printf("r = %d | g = %d | b = %d\n", color.t_rgba.r, color.t_rgba.g, color.t_rgba.b);
	return (color.c);

}
