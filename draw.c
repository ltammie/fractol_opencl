#include "includes/fractol.h"

static int 	linear_sin(int x, int max)
{
	int r;
	int g;
	int b;
	int intensity;

	if (x == max)
		return (0);
	intensity = M_PI_2 * x / max;
	r = (int)(sin(intensity) * 255);
	g = (int)(sin(intensity * 2) * 255);
	b = (int)(cos(intensity) * 255);

//	r = (r >> 16 | 0xff);
//	g = (g >> 8 | 0xff);
//	b = (b | 0xff);
	return (r << 16 | g << 8 | b);
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
	size_t global_size[] = {HEIGHT,WIDTH};
	clEnqueueNDRangeKernel(data->cl.queue, data->cl.kernel, dim, NULL, global_size, NULL, 0, NULL, NULL);
	clFinish(data->cl.queue);
	clEnqueueReadBuffer(data->cl.queue, output_buffer, CL_TRUE, 0, sizeof(int) * size, result, 0, NULL, NULL);
	clFinish(data->cl.queue);

//	printf("started drawing\n");
	for (int i = 0; i < HEIGHT ; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
			data->img.img_data[i * WIDTH + j] = linear_sin(result[i * WIDTH + j], data->max_iter);
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
