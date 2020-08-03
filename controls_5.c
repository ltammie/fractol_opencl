/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:43:02 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/03 18:51:41 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int		change_power(int key, t_mlx *data)
{
	if (key == U)
		data->v.power++;
	if (key == J)
		data->v.power--;
	data->v.power = data->v.power <= 0 ? 1 : data->v.power;
	data->v.power = data->v.power > 10 ? 10 : data->v.power;
	mlx_clear_window(data->mlx, data->win);
	mlx_do_sync(data->mlx);
	draw_image(data);
	return (0);
}
