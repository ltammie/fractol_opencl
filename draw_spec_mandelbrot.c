#include "includes/fractol.h"

static void spec_color(t_mlx *data)
{
	int i;
	int j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			data->img.img_data[i * WIDTH + j] = data->result[i * WIDTH + j];
			j++;
		}
		i++;
	}
}

int		draw_spec_mandelbrot(t_mlx *data)
{
	cl_mem output_buffer;

	output_buffer = clCreateBuffer(data->cl.context, CL_MEM_WRITE_ONLY, sizeof(float) * WIDTH * HEIGHT, NULL, NULL);
	clSetKernelArg(data->cl.kernel, 0, sizeof(int), &data->max_iter);
	clSetKernelArg(data->cl.kernel, 1, sizeof(float), &data->view.minX);
	clSetKernelArg(data->cl.kernel, 2, sizeof(float), &data->view.maxX);
	clSetKernelArg(data->cl.kernel, 3, sizeof(float), &data->view.minY);
	clSetKernelArg(data->cl.kernel, 4, sizeof(float), &data->view.maxY);
	clSetKernelArg(data->cl.kernel, 5, sizeof(cl_mem), &output_buffer);
	clEnqueueNDRangeKernel(data->cl.queue, data->cl.kernel, data->cl.dim, NULL,
						   data->cl.global_size, NULL, 0, NULL, NULL);
	clFinish(data->cl.queue);
	clEnqueueReadBuffer(data->cl.queue, output_buffer, CL_TRUE, 0, sizeof(float) * WIDTH * HEIGHT,
			data->result, 0, NULL, NULL);
	clFinish(data->cl.queue);

	spec_color(data);
	clReleaseMemObject(output_buffer);
	return (0);
}
