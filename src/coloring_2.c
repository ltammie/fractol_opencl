/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:06:12 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/04 13:11:24 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		zerg_2(float x, int max)
{
	float k;
	t_rgb color;

	if (x == max)
		return (BLACK);
	k = (x / max);
	color = hsv_to_rgb(250, 0.8, k);
	return (color.c);
}

int		dark_red(float i, int max)
{
	t_rgb color;
	float k;

	if (i == max)
		return (BLACK);
	k = i / (float)max;
	color.t_rgba.r = (int)(20 * (1 - k) * (k * k * k) * 255);
	color.t_rgba.g = (int)(1 * ((1 - k) * (1 - k)) * (k * k) * 255);
	color.t_rgba.b = (int)(1 * ((1 - k) * (1 - k) * (1 - k)) * k * 255);
	color.t_rgba.a = 0;
	return (color.c);
}

int		mixx(float i, int max)
{
	t_rgb color;
	float k;

	if (i == max)
		return (BLACK);
	k = i / (float)max;
	color.t_rgba.r = (int)(1 * ((1 - k) * (1 - k) * (1 - k)) * k * 255);
	color.t_rgba.g = (int)(15 * ((1 - k) * (1 - k)) * (k * k) * 255);
	color.t_rgba.b = (int)(20 * (1 - k) * (k * k * k) * 255);
	color.t_rgba.a = 0;
	return (color.c);
}
