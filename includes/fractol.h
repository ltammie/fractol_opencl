#ifndef FRACTOL_H
#define FRACTOL_H

# define WIDTH 1280
# define HEIGHT 720
# define MIN_RE -2.0f
# define MAX_RE 2.0f
# define MIN_IM -1.17f
# define MAX_IM 1.08f
# define ZOOM 0.9501f
# define OFFSET 0.05f

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include <OpenCL/opencl.h>
#include "keys.h"

//typedef struct	s_complex
//{
//	double		re;
//	double 		im;
//}				t_complex;

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
	float 		zoom;
	float 		minX;
	float 		maxX;
	float 		minY;
	float 		maxY;
	float 		offsetX;
	float 		offsetY;
	float 		prev_mouseX;
	float 		prev_mouseY;
	float 		mouseShiftX;
	float 		mouseShiftY;

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
}				t_cl;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_view		view;
	t_cl 		cl;
	char 		*fractal_type;
	int 		max_iter;
}				t_mlx;


/*
 ** ----------init functions---------
 */

t_mlx			*init_data(char *argv);
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
//void			*drawMandelbrot(void *data);
//int			mandelbrotIter(int x, int y, int max, t_view view);
//void			*drawJulia(void *data);
//int			juliaIteration(int x, int y, int max);
//float			draw_julia(t_mlx *data, int x, int y);
//
//float			map(float value, float fmin, float fmax, float tmin, float tmax);




/*
 ** -----complex numbers functions------
 */

//t_complex		complex_add_complex(t_complex n1, t_complex n2);
//t_complex		complex_sub_complex(t_complex n1, t_complex n2);
//t_complex		complex_mult_complex(t_complex n1, t_complex n2);
//double 		complex_abs(t_complex n);
//double 		complex_len(t_complex n);
//
//
//void			print_complex(t_complex n);



/*
 ** --------------controls--------------
 */

int				zoom(int key, t_mlx *data);
int				max_iter_change(int x, t_mlx *data);
int				refresh(int key, t_mlx *data);
int				redraw(int key, t_mlx *data);
int				arrow_move(int key, t_mlx *data);
int				mouse_move(int x, int y, t_mlx *data);
void			close_fractol(t_mlx *data);

/*
 ** ----------other functions---------
 */

void			error(int err);

#endif



