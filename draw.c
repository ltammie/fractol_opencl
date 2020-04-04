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
	printf("platfrom ret = %d\n", ret);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
	printf("device ret = %d\n", ret);
//	cl_uint tmp;
//	clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(tmp), &tmp, NULL);
//	printf("max compute_units = %d\n", tmp);
//	clGetDeviceInfo(device_id, CL_DEVICE_IMAGE_SUPPORT, sizeof(tmp), &tmp, NULL);
//	printf("image support = %s\n", tmp ? "true" : "false");;
//	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(tmp), &tmp, NULL);
//	printf("max dimensions = %d\n", tmp);
//	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(tmp), &tmp, NULL);
//	printf("max work_group size = %d\n", tmp);
//	size_t max_par;
//	clGetDeviceInfo(device_id, CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(size_t), &max_par, NULL);
//	printf("max kernel parameter size = %zu\n", max_par);


	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	printf("context ret = %d\n", ret);
	queue = clCreateCommandQueue(context, device_id, 0, &ret);
	printf("queue ret = %d\n", ret);


	/*
	 * считать код ядра
	 * массив строк кода ядра
	 */
	int		i;
	int		fd;
	size_t 	count;
	char	**source;
	char	*line;

	count = 0;
	line = NULL;
	if (((fd = open(krnlMandelbrot, O_RDONLY)) < 0) || ((read(fd, line, 0)) < 0))
		return (-1);

	/* узнаем размер файла - количество строк для массива **source */

	while (get_next_line(fd, &line))
	{
		count++;
		printf("line %zu: %s\n", count, line);
		free(line);
	}
	printf("lines count = %zu\n", count);
	close(fd);
	/* выделяем память под массив count-строк */
	source = (char **)malloc(sizeof(char *) * count);
	fd = open(krnlMandelbrot, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		size_t strlen = ft_strlen(line);
		printf("line %d length: %zu\n", i, strlen);
//		source[i] = (char *)malloc(sizeof(char) * strlen);
		source[i] = ft_strdup(line);
		printf("line %d: %s\n", i, source[i]);
		free(line);
		line = NULL;
		i++;
	}

	for (int j = 0; j < 12; ++j)
	{
		printf("%s\n", source[j]);
	}
	/* создать бинарник из кода программы */
	program = clCreateProgramWithSource(context, count, (const char **)source, NULL, &ret);
	printf("program creation ret = %d\n", ret);


	/* скомпилировать программу */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	printf("program build ret = %d\n", ret);

	size_t log_size;
	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	printf("log size ret = %d\n", ret);
	char *log = (char *)malloc(sizeof(char) * log_size);
	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	write(open("log.txt", O_WRONLY), log, log_size);

	/* создать кернел, передваемое имя - название kernela в файле .cl */
	kernel = clCreateKernel(program, "array_add", &ret);
	printf("kernel creation ret = %d\n", ret);


	float		result[50];
	int 	max_iter = data->max_iter;
	if (max_iter)
		;

	cl_mem output_buffer;

	output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 50, NULL, &ret);
	printf("buffer ret = %d\n", ret);
//	clSetKernelArg(kernel, 0, sizeof(int), &max_iter);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), &output_buffer);

	size_t dim = 2;
	size_t global_size[] = {5,10};
	clEnqueueNDRangeKernel(queue, kernel, dim, NULL, global_size, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(queue, output_buffer, CL_TRUE, 0, sizeof(float) * 50, result, 0, NULL, NULL);

//	for (int i = 0; i  < 50 ; i++)
//	{
//		printf("%d\n", result[i]);
//	}
	for (int i = 0; i < 5 ; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			printf("%f\t", result[i * 10 + j]);
		}
		printf("\n");
	}

	printf("free started\n");
	clReleaseMemObject(output_buffer);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);
	printf("free done\n");
//	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	return (0);
}
