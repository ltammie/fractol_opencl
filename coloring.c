#include "includes/fractol.h"

int				sin_coloring(int x)
{
	t_rgb color;

	color.rgba.r = sin(0.016 * x + 30) * 200 + 55;
	color.rgba.g = sin(0.013 * x + 15) * 200 + 55;
	color.rgba.b = sin(0.01 * x + 10) * 200 + 55;
	color.rgba.a = 0;
	return (color.c);
}

int				zerg(int i, int max)
{
	t_rgb color;

	if (i == max)
		return (BLACK);
	color.rgba.r = i * 6 % 255;
	color.rgba.g = 0;
	color.rgba.b = i * 6 % 255;
	color.rgba.a = 0;
	return (color.c);
}

int				basic_one(float i, int max)
{
	t_rgb color;
	float k;

	if (i == max)
		return (BLACK);
	k = i / (float)max;
	color.rgba.r = (int)(9 * (1 - k) * (k * k * k) * 255);
	color.rgba.g = (int)(15 * ((1 - k) * (1 - k)) * (k * k) * 255);
	color.rgba.b = (int)(8.5 * ((1 - k) * (1 - k) * (1 - k)) * k * 255);
	color.rgba.a = 0;
	return (color.c);
}
