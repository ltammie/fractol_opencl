#include "includes/fractol.h"

int		zoom(int key, t_mlx *data)
{
	float 	zoom;

	if ((key == MIN || key == RIGHT_MB) && data->view.zf > 1)
		data->view.zf -= 1.0f;
	if (key == PLUS || key == LEFT_MB)
		data->view.zf += 1.0f;
	zoom = powf(ZOOM, data->view.zf);
	data->view.zoom = zoom;
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
	printf("offsetX = %f, offsetY = %f\n", data->view.offsetX, data->view.offsetY);
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
		printf("minX = %.8f\tmaxX = %.8f\n",data->view.minX, data->view.maxX);
		printf("minY = %.8f\tmaxY = %.8f\n",data->view.minY, data->view.maxY);
		printf("iterations = %d\n", data->max_iter);
		mlx_clear_window(data->mlx, data->win);
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

