/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:06:57 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/03 18:49:28 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void			init_view(t_view *view)
{
	view->zf = 1.0f;
	view->min_x = -2.0f;
	view->max_x = 2.0f;
	view->min_y = -1.17f;
	view->max_y = 1.17f;
	view->angle = 0.0f;
	view->offset = 0.0f;
	view->color_type = 1;
	view->m_re = 0.0f;
	view->m_im = 0.0f;
	view->julia_re = 0.0f;
	view->julia_im = 0.0f;
	view->b = 0;
	view->pressed_button = -1;
	view->music_status = 0;
	view->julia_change_mod = 1;
	view->power = 1;
}

char			*return_fractal_type(int argv)
{
	if (argv == 1)
		return ("kernels/1_mandelbrot.cl");
	if (argv == 2)
		return ("kernels/2_julia.cl");
	if (argv == 3)
		return ("kernels/3_ship.cl");
	if (argv == 4)
		return ("kernels/4_wrong_phoenix.cl");
	if (argv == 5)
		return ("kernels/5_classic_phoenix.cl");
	if (argv == 6)
		return ("kernels/6_mbrot_spec_color.cl");
	if (argv == 7)
		return ("kernels/7_burning_julia.cl");
	if (argv == 8)
		return ("kernels/8_mbrot_z3.cl");
	if (argv == 9)
		return ("kernels/9_Tricorn.cl");
	return ("meow");
}

t_mlx			*init_data(int argv)
{
	t_mlx *data;

	if (!(data = (t_mlx *)malloc(sizeof(t_mlx))))
		error(MLX_MALLOC_ERROR);
	if (!(data->mlx = mlx_init()))
		error(MLX_INIT_ERROR);
	if (!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fractol")))
		error(MLX_MAIN_WINDOW_CREATE_ERROR);
	data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.img_data = (int *)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_l, &data->img.endian);
	data->help_status = 0;
	data->fractal_type = argv;
	data->cl_source = return_fractal_type(argv);
	init_view(&data->v);
	if (data->fractal_type == 3)
	{
		data->v.max_y -= 0.6f;
		data->v.min_y -= 0.6f;
	}
	data->max_iter = 100;
	data->res = (float *)malloc(sizeof(float) * (WIDTH * HEIGHT));
	return (data);
}
