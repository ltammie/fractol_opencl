#ifndef FRACTOL_H
#define FRACTOL_H

# ifndef GL_SILENCE_DEPRECATION
# define GL_SILENCE_DEPRECATION 1
# endif

# define WIDTH 1280
# define HEIGHT 720
# define HELP_WIDTH 600
# define HELP_HEIGHT 400
# define MIN_RE -2.0f
# define MAX_RE 2.0f
# define MIN_IM -1.17f
# define MAX_IM 1.17f
# define OFFSET 0.05f

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <OpenCL/opencl.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include "keys.h"
#include "color_schemes.h"
#include "error_codes.h"

typedef union	u_rgb
{
	unsigned int c;
	struct s_rgba
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	} t_rgba;
}				t_rgb;

typedef struct	s_image
{
	void		*img_ptr;
	int			*img_data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_image;

typedef	struct	s_view
{
	float 		zf;
	float 		minX;
	float 		maxX;
	float 		minY;
	float 		maxY;
	float 		offset;
	float 		prev_mouseX;
	float 		prev_mouseY;
	int			color_type;
	float		mouse_re;
	float		mouse_im;
	float		julia_re;
	float		julia_im;
	int 		b;
	int			pressed_button;
	int 		music_status;
	int 		julia_change_mod;
	int 		zoom_x;
	int 		zoom_y;

}				t_view;

typedef struct	s_cl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	char 				**kernel_source;
	int 				count;
	size_t 				dim;
	size_t				global_size[2];
}				t_cl;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*help;
	int			help_status;
	t_image		img;
	t_view		view;
	t_cl 		cl;
	int 		fractal_type;
	char		*cl_source;
	int 		max_iter;
	float		*result;
}				t_mlx;


/*
 ** ----------init functions---------
 */

t_mlx			*init_data(int argv);
void			init_view(t_view *view);

/*
 ** ----------OpenCl functions---------
 */

void			cl_init(t_cl *cl);
void			cl_free(t_cl *cl);
char			**get_kernel_source(t_cl *cl, char *type);

/*
 ** ----------draw functions---------
 */

int				draw_image(t_mlx *data);

/*
 ** --------------controls--------------
 */

int				zoom(int key, t_mlx *data, int x, int y);
int				max_iter_change(int x, t_mlx *data);
int				refresh(int key, t_mlx *data);
int				redraw(int key, t_mlx *data);
int				arrow_move(int key, t_mlx *data);
void			close_fractol(t_mlx *data);
int				change_julia(int x, int y, t_mlx *data);
int				help_menu(int key, t_mlx *data);
int				play_music(t_mlx *data);


/*
 ** --------coloring_functions----------
 */

int				zerg(float x, float max);
int				basic_one(float i, float max);
int				black_hole(float i, float max);
int				mix(float i, float max);
void			color_fractal(t_mlx *data);
int				change_color(int key, t_mlx *data);


/*
 ** ----------other functions---------
 */

void			error(int err);
t_rgb			new_rgb_color(unsigned char r, unsigned char g, unsigned char b);
t_rgb			hsv_to_rgb(float h, float s, float v);

#endif



