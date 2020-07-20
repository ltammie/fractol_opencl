#include "includes/fractol.h"

int 	play_music(t_mlx *data)
{
	if (data->view.music_status == 0)
	{
		data->view.music_status = 1;
		system("afplay Deb.mp3 &");
	}
	else
	{
		data->view.music_status = 0;
		system("killall afplay");
	}
	return (0);
}

int 	max_iter_change(int key, t_mlx *data)
{
	if (key == Q)
		data->max_iter -= 10;
	if (key == E)
		data->max_iter += 10;
	mlx_clear_window(data->mlx, data->win);
	draw_image(data);
	mlx_do_sync(data->mlx);
	return (0);
}

int 	change_angle(int key, t_mlx *data)
{
	if (key == AR_LEFT)
		data->view.angle -= 10.0f;
	if (key == AR_RIGHT)
		data->view.angle += 10.0f;
	if (data->view.angle < 0.0f)
		data->view.angle += 360.0f;
	if (data->view.angle > 360.0f)
		data->view.angle -= 360.0f;
	mlx_clear_window(data->mlx, data->win);
	draw_image(data);
	mlx_do_sync(data->mlx);
	return (0);
}
