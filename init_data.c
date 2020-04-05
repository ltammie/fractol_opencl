#include "includes/fractol.h"

void	init_view(t_view *view)
{
	view->zf = 1;
	view->minX = -2.0f;
	view->maxX = 2.0f;
	view->minY = -1.17f;
	view->maxY = 1.08f;
	view->prev_mouseX = 0.0f;
	view->prev_mouseY = 0.0f;
	view->mouseShiftX = 0.0f;
	view->mouseShiftY = 0.0f;
}

t_mlx	*init_data(char *argv)
{
	t_mlx *data;

	if (!(data = (t_mlx *)malloc(sizeof(t_mlx))))
		error(0);
	if (!(data->mlx = mlx_init()))
		error(0);
	if (!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fractol")))
		error(0);
	data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.img_data = (int *)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_l, &data->img.endian);
	data->fractal_type = argv;
	init_view(&data->view);
	data->cl.kernel_source = get_kernel_source(&data->cl);
	data->max_iter = 500;
	return(data);
}
