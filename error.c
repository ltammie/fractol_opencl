/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:06:55 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 15:06:55 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	error(int err)
{
	if (err == 1)
	{
		write(1, "usage: ./fractol {fractal_type}\n", 32);
		write(1, "List of available fractals types:\n", 34);
		write(1, "1 - Mandelbrot\n", 15);
		write(1, "2 - Julia\n", 10);
		write(1, "3 - Burning Ship\n", 17);
		write(1, "4 - Bad Phoenix\n", 16);
		write(1, "5 - Classic Phoenix\n", 20);
		write(1, "6 - Special Mandelbrot Coloring\n", 33);
		write(1, "7 - Burning Julia\n", 18);
		write(1, "8 - Mandelbrot Z^3\n", 19);
		write(1, "9 - Tricorn\n", 12);
		exit(0);
	}
	else
	{
		ft_putnbr(err);
		exit(0);
	}
}
