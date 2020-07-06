#include "includes/fractol.h"

void	init_view(t_view *view)
{
	view->zf = 1.0f;
	view->zoom = 1.0f;
	view->minX = -2.0f;
	view->maxX = 2.0f;
	view->minY = -1.17f;
	view->maxY = 1.17f;
	view->offsetX = 0.0f;
	view->offsetY = 0.0f;
	view->prev_mouseX = 0.0f;
	view->prev_mouseY = 0.0f;
	view->mouseShiftX = 0.0f;
	view->mouseShiftY = 0.0f;
}

static	char	*return_fractal_type(char *argv)
{
	if (!ft_strcmp(argv, "Mandelbrot"))
		return ("mandelbrot.cl");
	if (!ft_strcmp(argv, "Julia"))
		return ("julia.cl");
	if (!ft_strcmp(argv, "Ship"))
		return ("ship.cl");
	return ("meow");
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
	data->fractal_type = return_fractal_type(argv);
	init_view(&data->view);
	if (!ft_strcmp(data->fractal_type, "ship.cl"))
	{
		data->view.maxY -= 0.7f; //maybe do some other shit-trick here? cause zoom works strange because of this
		data->view.minY -= 0.7f;
	}
	data->max_iter = 50;
	return(data);
}
