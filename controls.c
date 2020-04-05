#include "includes/fractol.h"

static float 	map(float value, float fmin, float fmax, float tmin, float tmax)
{
	return ((value - fmin) * (tmax - tmin) / (fmax - fmin) + tmin);
}

int		zoom(int key, t_mlx *data)
{
	printf("---------zoom started--------\n");

	float 	zoom;

	if (key == MIN && data->view.zf > 1)
		data->view.zf -= 1.0f;
	if (key == PLUS)
		data->view.zf += 1.0f;
	zoom = powf(ZOOM, data->view.zf);
	data->view.zoom = zoom;
	data->view.minX = MIN_RE * zoom + data->view.offsetX;
	data->view.maxX = MAX_RE * zoom + data->view.offsetX;
	data->view.minY = MIN_IM * zoom + data->view.offsetY;
	data->view.maxY = MAX_IM * zoom + data->view.offsetY;
	mlx_clear_window(data->mlx, data->win);
	printf("draw_started\n");
	draw_image(data);
	printf("--------zoom finished----------\n");
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
	printf("offset x = %f\n", data->view.offsetX);
	printf("offset y = %f\n", data->view.offsetY);
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
		mlx_clear_window(data->mlx, data->win);
		draw_image(data);
	}
	return (0);
}


//not working need fix or recode

int 	mouse_move(int x, int y, t_mlx *data)
{
	data->view.mouseShiftX = data->view.prev_mouseX - x;
	data->view.mouseShiftY = data->view.prev_mouseY - y;
	data->view.prev_mouseX = x;
	data->view.prev_mouseY = y;
	printf("new x = %d\n", x);
	printf("new y = %d\n", y);

	data->view.mouseShiftX = map(data->view.mouseShiftX, 0, 1279, data->view.minX, data->view.maxX);
	data->view.mouseShiftY = map(data->view.mouseShiftY, -45, 754, data->view.minY, data->view.maxY);
	data->view.minX += data->view.mouseShiftX;
	data->view.maxX += data->view.mouseShiftX;
	data->view.minY += data->view.mouseShiftY;
	data->view.maxY += data->view.mouseShiftY;

	printf("shift X = %f\n", data->view.mouseShiftX);
	printf("shift Y = %f\n", data->view.mouseShiftY);

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
