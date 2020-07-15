#include "includes/fractol.h"

void	init_view(t_view *view)
{
	view->zf = 1.0f;
	view->minX = -2.0f;
	view->maxX = 2.0f;
	view->minY = -1.17f;
	view->maxY = 1.17f;
	view->offset = 0.0f;
	view->prev_mouseX = 0.0f;
	view->prev_mouseY = 0.0f;
	view->color_type = 1;
	view->mouse_re = 0.0f;
	view->mouse_im = 0.0f;
	view->julia_re = 0.0f;
	view->julia_im = 0.0f;
	view->b = 0;
	view->pressed_button = -1;
	view->music_status = 0;
	view->julia_change_mod = 0;
}

static	char	*return_fractal_type(int argv)
{
	if (argv == 1)
		return ("mandelbrot.cl");
	if (argv == 2)
		return ("julia.cl");
	if (argv == 3)
		return ("ship.cl");
	if (argv == 4)
		return ("wrong_phoenix.cl");
	if (argv == 5)
		return ("classic_phoenix.cl");
	return ("meow");
}

t_mlx	*init_data(int argv)
{
	t_mlx *data;

	if (!(data = (t_mlx *)malloc(sizeof(t_mlx))))
		error(MLX_MALLOC_ERROR);
	if (!(data->mlx = mlx_init()))
		error(MLX_INIT_ERROR);
	if (!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fractol")))
		error(MLX_MAIN_WINDOW_CREATE_ERROR);
	data->help_status = 0;
	data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.img_data = (int *)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_l, &data->img.endian);
	data->fractal_type = argv;
	data->cl_source = return_fractal_type(argv);
	init_view(&data->view);
	if (data->fractal_type == 3)
	{
		data->view.maxY -= 0.6f;
		data->view.minY -= 0.6f;
	}
	data->max_iter = 100;
	data->result = (float *)malloc(sizeof(float) * (WIDTH * HEIGHT));
	return(data);
}
