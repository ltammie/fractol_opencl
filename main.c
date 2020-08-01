/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:07:06 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 15:44:32 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static	void	check_argv(int type)
{
	if (type != 1 && type != 2 && type != 3
	&& type != 4 && type != 5 && type != 6)
		error(1);
}

int				main(int argc, char **argv)
{
	t_mlx *data;

	if (argc != 2)
		error(1);
	check_argv(ft_atoi(argv[1]));
	data = init_data(ft_atoi(argv[1]));
	data->cl.kernel_source = get_kernel_source(&data->cl, data->cl_source);
	cl_init(&data->cl);
	draw_image(data);
	mlx_hook(data->win, 2, 0, key_press, data);
	mlx_hook(data->win, 3, 0, key_release, data);
	mlx_hook(data->win, 4, 0, mouse_button_press, data);
	mlx_hook(data->win, 5, 0, mouse_button_release, data);
	mlx_hook(data->win, 6, 0, change_julia, data);
	mlx_loop_hook(data->mlx, no_events, data);
	mlx_loop(data->mlx);
	return (0);
}
