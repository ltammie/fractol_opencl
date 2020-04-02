#include "includes/fractol.h"

int main()
{
	cl_int				ret;
	cl_context			context;
	cl_command_queue	command_queue;

	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_device_id		device_id;
	cl_uint 			ret_num_devices;

	/* получить доступные платформы */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);

	/* получить доступные устройства */
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

	/* создать контекст */
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	/* создать очередь команд */
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

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
		printf("%s\n", line);
		free(line);
		i++;
	}

	/* создать бинарник из кода программы */
	program = clCreateProgramWithSource(context, 1, (const char **)&source, NULL, &ret);

	/* скомпилировать программу */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	/* создать кернел, передваемое имя - название kernela в файле .cl */
	kernel = clCreateKernel(program, "test", &ret);

	cl_mem memobj = NULL;
	int memLenth = 10;
	cl_int* mem = (cl_int *)malloc(sizeof(cl_int) * memLenth);

	/* создать буфер */
	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, memLenth * sizeof(cl_int), NULL, &ret);

	/* записать данные в буфер
	 * clEnqueueWriteBuffer записывает данные из массива mem в буфер memobj
	 */
	ret = clEnqueueWriteBuffer(command_queue, memobj, CL_TRUE, 0, memLenth * sizeof(cl_int), mem, 0, NULL, NULL);

	/* устанавливаем параметр */
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);

	size_t global_work_size[1] = { 10 };

	/* выполнить кернел */
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);

	/* считать данные из буфера */
	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, memLenth * sizeof(float), mem, 0, NULL, NULL);

	return 0;
}
