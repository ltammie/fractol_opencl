#include "includes/fractol.h"

int		zoom(int key, t_mlx *data)
{
	printf("---------zoom started--------\n");
	float 	zoom;

	zoom = 0.9501f;
	if (key == MIN)
	{
//		if (data->view.minX > -2.0f && data->view.maxX < 2.0f
//			&& data->view.minY > -1.17f && data->view.maxY < 1.0f)
//		{
			data->view.minX /= zoom;
			data->view.maxX /= zoom;
			data->view.minY /= zoom;
			data->view.maxY /= zoom;
//		}
	}
	if (key == PLUS)
	{
		data->view.minX *= zoom;
		data->view.maxX *= zoom;
		data->view.minY *= zoom;
		data->view.maxY *= zoom;
	}
	mlx_clear_window(data->mlx, data->win);
	printf("draw_started\n");
	draw_image(data);
	printf("--------zoom finished----------\n");
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

//int 	mouse_move(int x, int y, t_mlx *data)
//{
//	data->view.mouseShiftX = data->view.prev_mouseX - x;
//	data->view.mouseShiftY = data->view.prev_mouseY - y;
//	data->view.prev_mouseX = x;
//	data->view.prev_mouseY = y;
//
//	printf("prev_mouseX = %f\n", data->view.prev_mouseX);
//	printf("prev_mouseY = %f\n", data->view.prev_mouseY);
//
//	return (0);
//}

void	close_fractol(t_mlx *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	(void)data;
	exit(0);
}
