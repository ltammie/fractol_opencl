#include "includes/fractol.h"

int		zoom(int key, t_mlx *data, int x, int y)
{
	float 	zoom;

	if ((key == MIN || key == RIGHT_MB) && data->view.zf > 1)
		data->view.zf -= 1.0f;
	if (key == PLUS || key == LEFT_MB)
		data->view.zf += 1.0f;
	zoom = powf(ZOOM, data->view.zf);
	data->view.zoom = zoom;
	data->view.offsetX += MAX_RE / (WIDTH / 2.0) * (x - 640) * zoom;
	if (y >= 360)
		data->view.offsetY += MIN_IM / (HEIGHT / 2.0)  * (360 - y) * zoom;
	else
		data->view.offsetY -= MAX_IM / (HEIGHT / 2.0)  * (360 - y) * zoom;
	data->view.minX = MIN_RE * zoom + data->view.offsetX;
	data->view.maxX = MAX_RE * zoom + data->view.offsetX;
	data->view.minY = MIN_IM * zoom + data->view.offsetY;
	data->view.maxY = MAX_IM * zoom + data->view.offsetY;
	mlx_clear_window(data->mlx, data->win);
	draw_image(data);
	return (0);
}

int 	arrow_move(int key, t_mlx *data)
{
	float	offset;
	float	zoom;

	zoom = data->view.zoom;
	offset = OFFSET * zoom;
	if (key == A)
		data->view.offsetX -= offset;
	if (key == D)
		data->view.offsetX += offset;
	if (key == W)
		data->view.offsetY -= offset;
	if (key == S)
		data->view.offsetY += offset;
	data->view.minX = MIN_RE * zoom + data->view.offsetX;
	data->view.maxX = MAX_RE * zoom + data->view.offsetX;
	data->view.minY = MIN_IM * zoom + data->view.offsetY;
	data->view.maxY = MAX_IM * zoom + data->view.offsetY;
	mlx_clear_window(data->mlx, data->win);
	draw_image(data);
	return (0);
}

int 	max_iter_change(int key, t_mlx *data)
{
	if (key == Q)
		data->max_iter--;
	if (key == E)
		data->max_iter++;
	mlx_clear_window(data->mlx, data->win);
	draw_image(data);
	return (0);
}

int		change_color(int key, t_mlx *data)
{
	if (key == ONE)
		data->view.color_type = 1;
	if (key == TWO)
		data->view.color_type = 2;
	if (key == THREE)
		data->view.color_type = 3;
	color_fractal(data);
	return (0);
}

