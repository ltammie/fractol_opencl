#include "includes/fractol.h"

void	error(int err)
{
	if (err == 1)
	{
		write(1, "usage: ./fractol {fractal_type}\n", 32);
		write(1, "List of available fractals types:\n", 34);
		write(1, "Mandelbrot\n", 11);
		write(1, "Julia\n", 6);
		exit(0);
	}
	else if (err == 2)
	{
		write(1, "invalid map\n", 12);
		exit(0);
	}
	else
	{
		write(1, "error\n", 6);
		exit(0);
	}
}
