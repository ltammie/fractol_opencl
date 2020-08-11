#include "../includes/fractol.h"

int		play_music(t_mlx *data)
{
	if (data->v.music_status == 0)
	{
		data->v.music_status = 1;
		system("afplay src/Deb.mp3 &");
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
