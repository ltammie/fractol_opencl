#include "includes/fractol.h"

int main()
{
	cl_int				ret;
	cl_context			context;
	cl_command_queue	queue;

	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_device_id		device_id;
	cl_uint 			ret_num_devices;

	/* получить доступные платформы */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);

	/* получить доступные устройства */
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

	/* check it later */
//	cl_int max_dims;
//	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
//			sizeof(max_dims), &max_dims, NULL);
//	printf("Preferred max dims: %d\n", max_dims);

	/* создать контекст */
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	/* создать очередь команд */
	queue = clCreateCommandQueue(context, device_id, 0, &ret);

	cl_program program = NULL;
	cl_kernel kernel = NULL;

	/*
	 * считать код ядра
	 * массив строк кода ядра
	 */
	int		i;
	int 	strlen;
	int		fd;
	int 	count;
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
	close(fd);
	/* выделяем память под массив count-строк */
	source = (char **)malloc(sizeof(char *) * count);
	fd = open(krnlMandelbrot, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		strlen = ft_strlen(line);
		source[i] = (char *)malloc(sizeof(char) * strlen);
		ft_strcpy(source[i], line);
//		printf("%s\n", line);
		free(line);
		i++;
	}

	/* создать бинарник из кода программы */
	program = clCreateProgramWithSource(context, 1, (const char **)&source, NULL, &ret);

	/* скомпилировать программу */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	/* создать кернел, передваемое имя - название kernela в файле .cl */
	kernel = clCreateKernel(program, "array_add", &ret);

	int data[24];
	int result[24];

	for (int j = 0; j < 24; ++j)
	{
		data[j] = j + 1;
	}

	cl_mem input_buffer;
	cl_mem output_buffer;

	input_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * 24, data, &ret);
	output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * 24, NULL, &ret);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_buffer);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &output_buffer);

	size_t dim = 1;
	size_t global_size = 24;
	ret = clEnqueueNDRangeKernel(queue, kernel, dim, NULL, &global_size, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(queue, output_buffer, CL_TRUE, 0, sizeof(int) * 24, result, 0, NULL, NULL);

	for (int j = 0; j < 24; ++j)
	{
		printf("result[%d] = %d\n", j + 1, result[j]);
	}
	return 0;
}
