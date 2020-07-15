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
