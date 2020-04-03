#include "includes/fractol.h"

//static	int		get_color(float brightness)
//{
//	int	r;
//	int	g;
//	int	b;
//
//	if (brightness <= 0.2)
//		brightness = 0;
//	r = (0xff0000 >> 16 | 0xff) * brightness;
//	g = (0x02ff00 >> 8 | 0xff) * brightness;
//	b = (0x03ff00 | 0xff) * brightness;
//	return (r << 16 | g << 8 | b);
//}

int		draw_image(t_mlx *data)
{
	cl_int				ret;
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;

	ret = clGetPlatformIDs(1, &platform_id, NULL);

	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);

	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	queue = clCreateCommandQueue(context, device_id, 0, &ret);

	/*
	 * считать код ядра
	 * массив строк кода ядра
	 */
	int		i;
	int 	strlen;
	int		fd;
	size_t 	count;
	char	**source;
	char	*line;


	i = 0;
	count = 0;
	line = NULL;
	if (((fd = open(krnlMandelbrot, O_RDONLY)) < 0) || ((read(fd, line, 0)) < 0))
		return (-1);

	/* узнаем размер файла - количество строк для массива **source */

	while (get_next_line(fd, &line))
	{
		count++;
		free(line);
	}
	printf("str count = %zu\n", count);
	close(fd);
	/* выделяем память под массив count-строк */
	source = (char **)malloc(sizeof(char *) * count);
	fd = open(krnlMandelbrot, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		strlen = ft_strlen(line);
		source[i] = (char *)malloc(sizeof(char) * strlen);
		ft_strcpy(source[i], line);
		free(line);
		i++;
	}

	/* создать бинарник из кода программы */
	program = clCreateProgramWithSource(context, count, (const char **)source, NULL, &ret);

	/* скомпилировать программу */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	/* создать кернел, передваемое имя - название kernela в файле .cl */
	kernel = clCreateKernel(program, "array_add", &ret);

	int		result[WIDTH][HEIGHT];

	cl_mem output_buffer;

	output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * WIDTH * HEIGHT, NULL, &ret);
	clSetKernelArg(kernel, 0, sizeof(data->max_iter), &data->max_iter);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &output_buffer);

	size_t dim = 2;
	size_t offset[] = {0, 0};
	size_t global_size[] = {WIDTH, HEIGHT};
	clEnqueueNDRangeKernel(queue, kernel, dim, offset, global_size, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(queue, output_buffer, CL_TRUE, 0, sizeof(int) * WIDTH * HEIGHT, result, 0, NULL, NULL);
	clReleaseMemObject(output_buffer);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);

	i = 0;
	int j;
	while (i < IMH)
	{
		j = 0;
		while (j < IMW)
		{
			printf("value = %d\n", result[j][i]);
//			data->img.img_data[i * IMW + j] = get_color((float)result[j][i] / (float)data->max_iter);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	return (0);
}
