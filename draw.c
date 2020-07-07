#include "includes/fractol.h"

//static int sin_coloring(int x)
//{
//	COLOR4 color;
//
//	color.rgba.r = sin(0.016 * x + 30) * 200 + 55;
//	color.rgba.g = sin(0.013 * x + 15) * 200 + 55;
//	color.rgba.b = sin(0.01 * x + 10) * 200 + 55;
//	color.rgba.a = 0;
//
//	return (color.c);
//}

//static int zerg_theme(int i, int max)
//{
//	if (i == max)
//		return (BLACK);
//	t_rgb color;
//
//	color.rgba.r = i * 6 % 255;
//	color.rgba.g = ;
//	color.rgba.b = i * 6 % 255;
//	color.rgba.a = 0;
//
//	return (color.c);
//}

static float gradient(float start, float end, float i)
{
	return(i * start + i * end);
}

//static int color_1(float i, int max)
//{
//	t_rgb color;
//	float k;
//
//	if (i == max)
//		return (BLACK);
//	k = i / (float)max;
//	color.rgba.r = (int)(9 * (1 - k) * (k * k * k) * 255);
//	color.rgba.g = (int)(15 * ((1 - k) * (1 - k)) * (k * k) * 255);
//	color.rgba.b = (int)(8.5 * ((1 - k) * (1 - k) * (1 - k)) * k * 255);
//	color.rgba.a = 0;
//	return (color.c);
//}

static int color_2(float i, int max)
{
	t_rgb color;

	if (i == max)
		return (BLACK);
	color.rgba.r = (int)gradient((RED >> 16) & 0xFF, (YELLOW >> 16) & 0xFF, i);
	color.rgba.g = (int)gradient((RED >> 8) & 0xFF, (YELLOW >> 8) & 0xFF, i);
	color.rgba.b = (int)gradient(RED & 0xFF, YELLOW & 0xFF, i);
	color.rgba.a = 0;
	return (color.c);
}

int		draw_image(t_mlx *data)
{
	cl_init(&data->cl);
	cl_int				ret;

	int 	size = WIDTH * HEIGHT;
	int		*result;

	result = (int *)malloc(sizeof(int) * size);
	cl_mem output_buffer;

	output_buffer = clCreateBuffer(data->cl.context, CL_MEM_WRITE_ONLY, sizeof(int) * size, NULL, &ret);
//	printf("buffer ret = %d\n", ret);
	clSetKernelArg(data->cl.kernel, 0, sizeof(int), &data->max_iter);
	clSetKernelArg(data->cl.kernel, 1, sizeof(float), &data->view.minX);
	clSetKernelArg(data->cl.kernel, 2, sizeof(float), &data->view.maxX);
	clSetKernelArg(data->cl.kernel, 3, sizeof(float), &data->view.minY);
	clSetKernelArg(data->cl.kernel, 4, sizeof(float), &data->view.maxY);
	clSetKernelArg(data->cl.kernel, 5, sizeof(cl_mem), &output_buffer);

	size_t dim = 2;
	size_t global_size[] = {WIDTH,HEIGHT};
	clEnqueueNDRangeKernel(data->cl.queue, data->cl.kernel, dim, NULL, global_size, NULL, 0, NULL, NULL);
	clFinish(data->cl.queue);
	clEnqueueReadBuffer(data->cl.queue, output_buffer, CL_TRUE, 0, sizeof(int) * size, result, 0, NULL, NULL);
	clFinish(data->cl.queue);

//	printf("started drawing\n");
	for (int i = 0; i < HEIGHT ; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
			data->img.img_data[i * WIDTH + j] = color_2(result[i * WIDTH + j], data->max_iter);
	}
//	printf("finished drawing\n");

//	printf("----------started free------------\n");
	cl_free(&data->cl);
	ret = clReleaseMemObject(output_buffer);
//	printf("output free ret = %d\n", ret);
//	printf("----------finished free------------\n");
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
//	printf("image put\n");
	return (0);
}
