/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:06:36 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 15:39:35 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static	float	interpolate(float start, float end, float interpolation)
{
	return (start + ((end - start) * interpolation));
}

int				zoom(int key, t_mlx *d, int x, int y)
{
	float interpolation;

	interpolation = 1.0f;
	if ((key == RIGHT_MB || key == WHEEL_DOWN) && d->v.zf > 1)
	{
		d->max_iter -= 3;
		d->v.zf -= 1.0f;
		interpolation = 1.0f / (1.0f / 1.02f);
	}
	else if (key == LEFT_MB || key == WHEEL_UP)
	{
		d->max_iter += 3;
		d->v.zf += 1.0f;
		interpolation = 1.0f / 1.02f;
	}
	d->v.m_re = (float)x / (WIDTH / (d->v.max_x - d->v.min_x)) + d->v.min_x;
	d->v.m_im = (float)y / (HEIGHT / (d->v.max_y - d->v.min_y)) + d->v.min_y;
	d->v.min_x = interpolate(d->v.m_re, d->v.min_x, interpolation);
	d->v.min_y = interpolate(d->v.m_im, d->v.min_y, interpolation);
	d->v.max_x = interpolate(d->v.m_re, d->v.max_x, interpolation);
	d->v.max_y = interpolate(d->v.m_im, d->v.max_y, interpolation);
	draw_image(d);
	mlx_do_sync(d->mlx);
	return (0);
}

int				arrow_move(int key, t_mlx *data)
{
	data->v.offset = OFFSET * (1.0f /
			(float)(pow(1.02f, (double)data->v.zf)));
	if (key == AR_LEFT)
	{
		data->v.min_x += data->v.offset * -1;
		data->v.max_x += data->v.offset * -1;
	}
	if (key == AR_RIGHT)
	{
		data->v.min_x += data->v.offset * 1;
		data->v.max_x += data->v.offset * 1;
	}
	if (key == AR_UP)
	{
		data->v.min_y += data->v.offset * -1;
		data->v.max_y += data->v.offset * -1;
	}
	if (key == AR_DOWN)
	{
		data->v.min_y += data->v.offset * 1;
		data->v.max_y += data->v.offset * 1;
	}
	draw_image(data);
	mlx_do_sync(data->mlx);
	return (0);
}

int				change_julia(int x, int y, t_mlx *data)
{
	float re_factor;
	float im_factor;

	if (data->v.julia_change_mod == 1)
	{
		re_factor = (MAX_RE - MIN_RE) / (WIDTH);
		im_factor = (MAX_IM - MIN_IM) / (HEIGHT);
		data->v.julia_re = MIN_RE + (float)x * re_factor;
		data->v.julia_im = MAX_IM - (float)y * im_factor;
		draw_image(data);
		mlx_do_sync(data->mlx);
	}
	return (0);
}

int				change_color(int key, t_mlx *data)
{
	if (key == ONE)
		data->v.color_type = 1;
	if (key == TWO)
		data->v.color_type = 2;
	if (key == THREE)
		data->v.color_type = 3;
	if (key == FOUR)
		data->v.color_type = 4;
	color_fractal(data);
	mlx_do_sync(data->mlx);
	return (0);
}
