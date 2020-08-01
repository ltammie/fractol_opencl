/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:06:53 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 18:36:36 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"
#include <stdio.h>

static	void	spec_color(t_mlx *data)
{
	int i;
	int j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			data->img.img_data[i * WIDTH + j] =
					(int)data->res[i * WIDTH + j];
			j++;
		}
		i++;
	}
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

static	void	load_basic_args(t_mlx *data)
{
	clSetKernelArg(data->cl.kernel, 0, sizeof(int), &data->max_iter);
	clSetKernelArg(data->cl.kernel, 1, sizeof(float), &data->v.min_x);
	clSetKernelArg(data->cl.kernel, 2, sizeof(float), &data->v.max_x);
	clSetKernelArg(data->cl.kernel, 3, sizeof(float), &data->v.min_y);
	clSetKernelArg(data->cl.kernel, 4, sizeof(float), &data->v.max_y);
}

static	void	load_julia_args(t_mlx *data)
{
	clSetKernelArg(data->cl.kernel, 6, sizeof(float), &data->v.julia_re);
	clSetKernelArg(data->cl.kernel, 7, sizeof(float), &data->v.julia_im);
}

int				draw_image(t_mlx *data)
{
	cl_mem output_buffer;

	mlx_clear_window(data->mlx, data->win);
	output_buffer = clCreateBuffer(data->cl.context, CL_MEM_WRITE_ONLY,
			sizeof(float) * WIDTH * HEIGHT, NULL, NULL);
	load_basic_args(data);
	if (data->fractal_type == 2)
		load_julia_args(data);
	if (data->fractal_type == 6)
		clSetKernelArg(data->cl.kernel, 6, sizeof(float), &data->v.angle);
	clSetKernelArg(data->cl.kernel, 5, sizeof(cl_mem), &output_buffer);
	clEnqueueNDRangeKernel(data->cl.queue, data->cl.kernel, data->cl.dim, NULL,
			data->cl.global_size, NULL, 0, NULL, NULL);
	clFinish(data->cl.queue);
	clEnqueueReadBuffer(data->cl.queue, output_buffer, CL_TRUE, 0,
			sizeof(float) * WIDTH * HEIGHT,
						data->res, 0, NULL, NULL);
	clFinish(data->cl.queue);
	if (data->fractal_type != 6)
		color_fractal(data);
	else
		spec_color(data);
	clReleaseMemObject(output_buffer);
	return (0);
}
