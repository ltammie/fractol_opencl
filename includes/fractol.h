#ifndef FRACTOL_H
#define FRACTOL_H

# define WIDTH 1280
# define HEIGHT 720
# define IMW 1280
# define IMH 720
# define krnlMandelbrot "krnl.cl"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include <OpenCL/opencl.h>
#include "keys.h"

typedef struct	s_complex
{
	double		re;
	double 		im;
}				t_complex;

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
	float 		minValue;
	float 		maxValue;
}				t_view;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_view 		view;
	char 		*fractal_type;
	int 		max_iter;
	int 		x;
	int 		y;
}				t_mlx;


/*
 ** ----------start functions---------
 */


t_mlx			*init_data(char *argv);

/*
 ** ----------draw functions---------
 */

int			draw_image(t_mlx *data);
void			draw_background(t_mlx *data);
void			*drawMandelbrot(void *data);
int				mandelbrotIter(int x, int y, int max, t_view view);
void			*drawJulia(void *data);
int				juliaIteration(int x, int y, int max);
float			draw_julia(t_mlx *data, int x, int y);

float 	map(float value, float fmin, float fmax, float tmin, float tmax);




/*
 ** -----complex numbers functions------
 */

t_complex		complex_add_complex(t_complex n1, t_complex n2);
t_complex		complex_sub_complex(t_complex n1, t_complex n2);
t_complex		complex_mult_complex(t_complex n1, t_complex n2);
double 			complex_abs(t_complex n);
double 			complex_len(t_complex n);


void			print_complex(t_complex n);



/*
 ** --------------controls--------------
 */

void			close_fractol(t_mlx *data);
int				zoom(int key, t_mlx *data);


/*
 ** ----------other functions---------
 */

void			error(int err);

#endif



