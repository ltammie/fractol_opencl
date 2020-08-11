#include "../includes/fractol.h"

int		change_power(int key, t_mlx *data)
{
	int tmp_p;

	tmp_p = data->v.power;
	if (key == U)
		tmp_p++;
	if (key == J)
		tmp_p--;
	init_view(&data->v, data->fractal_type);
	data->v.power = tmp_p <= 0 ? 1 : tmp_p;
	data->v.power = tmp_p > 10 ? 10 : tmp_p;
	data->max_iter = 100;
	mlx_clear_window(data->mlx, data->win);
	mlx_do_sync(data->mlx);
	draw_image(data);
	return (0);
}
