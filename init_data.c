#include "includes/fractol.h"

t_mlx	*init_data(char *argv)
{
	t_mlx *data;

	if (!(data = (t_mlx *)malloc(sizeof(t_mlx))))
		error(0);
	if (!(data->mlx = mlx_init()))
		error(0);
	if (!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fractol")))
		error(0);
	data->img.img_ptr = mlx_new_image(data->mlx, IMW, IMH);
	data->img.img_data = (int *)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_l, &data->img.endian);
	data->view.minValue = -2.0f;
	data->view.maxValue = 1.0f;
	data->fractal_type = argv;
	data->max_iter = 500;
	return(data);
}
