/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:06:48 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 18:56:21 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int		play_music(t_mlx *data)
{
	if (data->v.music_status == 0)
	{
		data->v.music_status = 1;
		system("afplay Deb.mp3 &");
	}
	else
	{
		data->v.music_status = 0;
		system("killall afplay");
	}
	return (0);
}

int		max_iter_change(int key, t_mlx *data)
{
	if (key == Q)
		data->max_iter -= 10;
	if (key == E)
		data->max_iter += 10;
	draw_image(data);
	mlx_do_sync(data->mlx);
	return (0);
}

int		change_angle(int key, t_mlx *data)
{
	if (key == A)
		data->v.angle -= 10.0f;
	if (key == D)
		data->v.angle += 10.0f;
	if (data->v.angle < 0.0f)
		data->v.angle += 360.0f;
	if (data->v.angle > 360.0f)
		data->v.angle -= 360.0f;
	draw_image(data);
	mlx_do_sync(data->mlx);
	return (0);
}

int		change_fractal_type(int key, t_mlx *data)
{
	if (key == LESS_B)
		data->fractal_type--;
	if (key == MORE_B)
		data->fractal_type++;
	data->fractal_type = data->fractal_type > 9 ? 1 : data->fractal_type;
	data->fractal_type = data->fractal_type == 0 ? 9 : data->fractal_type;
	cl_free(&data->cl);
	init_view(&data->v);
	if (data->fractal_type == 3)
	{
		data->v.max_y -= 0.6f;
		data->v.min_y -= 0.6f;
	}
	data->cl_source = return_fractal_type(data->fractal_type);
	data->max_iter = 100;
	data->cl.kernel_source = get_kernel_source(&data->cl, data->cl_source);
	cl_init(&data->cl);
	draw_image(data);
	mlx_do_sync(data->mlx);
	return (0);
}

int		key_release(int key, t_mlx *data)
{
	if (key == MORE_B || key == LESS_B)
		change_fractal_type(key, data);
	return (0);
}
