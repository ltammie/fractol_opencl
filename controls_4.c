/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colontrols3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:45:08 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/03 19:22:55 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int		mouse_button_release(int button, int x, int y, t_mlx *data)
{
	if (button == LEFT_MB || button == RIGHT_MB)
		if (x && y)
			data->v.b = 0;
	return (0);
}

int		mouse_button_press(int button, int x, int y, t_mlx *data)
{
	if (button == LEFT_MB || button == RIGHT_MB
		|| button == WHEEL_UP || button == WHEEL_DOWN)
	{
		data->v.b = 1;
		data->v.pressed_button = button;
		data->v.zoom_x = x;
		data->v.zoom_y = y;
		zoom(button, data, x, y);
		if (button == WHEEL_UP || button == WHEEL_DOWN)
			data->v.b = 0;
	}
	return (0);
}

int		no_events(t_mlx *data)
{
	if (data->v.b == 1)
		zoom(data->v.pressed_button, data, data->v.zoom_x, data->v.zoom_y);
	return (0);
}

int		key_press(int key, t_mlx *data)
{
	if (key == AR_LEFT || key == AR_RIGHT || key == AR_DOWN || key == AR_UP)
		arrow_move(key, data);
	if (key == Q || key == E)
		max_iter_change(key, data);
	if ((key == A || key == D) && data->fractal_type == 6)
		change_angle(key, data);
	if (key == R)
		refresh(key, data);
	if (key == H)
		help_menu(key, data);
	if (key == P)
		play_music(data);
	if (key == M)
		data->v.julia_change_mod = (data->v.julia_change_mod == 1) ? 0 : 1;
	if ((key == U || key == J) && data->fractal_type != 4 && data->fractal_type != 5 && data->fractal_type != 8)
		change_power(key, data);
	if (key == SPACE)
		redraw(key, data);
	if (key == ONE || key == TWO || key == THREE || key == FOUR)
		change_color(key, data);
	if (key == ESC)
		close_fractol(data);
	return (0);
}

int		show_menu(t_mlx *d)
{
	mlx_string_put(d->mlx, d->help, 20, 15, WHITE,
			"LMB | RMB | WHEEL_UP | WHEEL_DOWN - zoom in/out");
	mlx_string_put(d->mlx, d->help, 20, 35, WHITE,
			"ARROWS - move left/right/up and down");
	mlx_string_put(d->mlx, d->help, 20, 55, WHITE,
			"1/2/3/4 - change colors");
	mlx_string_put(d->mlx, d->help, 20, 75, WHITE,
			"Q | E - change maximum iterations");
	mlx_string_put(d->mlx, d->help, 20, 95, WHITE,
				   "U | J - increase / decrease fractal power");
	mlx_string_put(d->mlx, d->help, 20, 115, WHITE,
			"R - refresh image");
	mlx_string_put(d->mlx, d->help, 20, 135, WHITE,
			"SPACE - change settings to default");
	mlx_string_put(d->mlx, d->help, 20, 155, WHITE,
			"P - play/stop music");
	mlx_string_put(d->mlx, d->help, 20, 175, WHITE, "M - Enable/Disable "
	"Julia set change with mouse (only for Julia set aka 2)");
	mlx_string_put(d->mlx, d->help, 20, 195, WHITE, "A / D - Change angle"
	" (only for Mandelbrot set special coloring mode)");
	mlx_string_put(d->mlx, d->help, 20, 215, WHITE,
			"P - play/stop music");
	mlx_string_put(d->mlx, d->help, 20, 235, WHITE,
			"H - show/hide help menu");
	mlx_string_put(d->mlx, d->help, 20, 255, WHITE,
			"ESC - close program :(");
	return (0);
}
