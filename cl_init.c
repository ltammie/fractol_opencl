/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sauron <sauron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 12:23:20 by sauron            #+#    #+#             */
/*   Updated: 2020/04/05 15:19:42 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static int get_lines(int fd)
{
	int		count;
	char 	*line;

	count = 0;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		count++;
		free(line);
	}
	return (count);
}

char	**get_kernel_source(t_cl *cl)
{
	int		i;
	int		fd;
	char	**source;
	char	*line;

	line = NULL;
	fd = 0;
	if (((fd = open(krnlMandelbrot, O_RDONLY)) < 0) || ((read(fd, line, 0)) < 0))
		error(0);
	cl->count = get_lines(fd);
	close(fd);
	source = (char **)malloc(sizeof(char *) * cl->count);
	fd = open(krnlMandelbrot, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		source[i] = ft_strdup(line);
		free(line);
		line = NULL;
		i++;
	}
	close(fd);
	return (source);
}

void	cl_init(t_cl *cl)
{
	cl_int				ret;


	ret = clGetPlatformIDs(1, &cl->platform_id, NULL);
	printf("platfrom ret = %d\n", ret);
	ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, 1, &cl->device_id, NULL);
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

	cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL, &ret);
	printf("context ret = %d\n", ret);


//	cl->kernel_source = get_kernel_source(cl);
	cl->program = clCreateProgramWithSource(cl->context, cl->count, (const char **)cl->kernel_source, NULL, &ret);
	printf("program creation ret = %d\n", ret);
//	for (int i = 0; i < cl->count ; ++i)
//		free(cl->kernel_source[i]);
//	free(cl->kernel_source);


	/* скомпилировать программу */
	ret = clBuildProgram(cl->program, 1, &cl->device_id, NULL, NULL, NULL);
	printf("program build ret = %d\n", ret);

//	size_t log_size;
//	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
//	printf("log size ret = %d\n", ret);
//	char *log = (char *)malloc(sizeof(char) * log_size);
//	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
//	write(open("log.txt", O_WRONLY), log, log_size);

	/* создать кернел, передваемое имя - название kernela в файле .cl */
	cl->kernel = clCreateKernel(cl->program, "array_add", &ret);
	printf("kernel creation ret = %d\n", ret);
	cl->queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &ret);
	printf("queue ret = %d\n", ret);
	printf("source code read\n");
}

void	cl_free(t_cl *cl)
{
	cl_int				ret;

	ret = clReleaseKernel(cl->kernel);
	printf("kernel free ret = %d\n", ret);
	ret = clReleaseProgram(cl->program);
	printf("program free ret = %d\n", ret);
	ret = clReleaseCommandQueue(cl->queue);
	printf("queue free ret = %d\n", ret);
	ret = clReleaseContext(cl->context);
	printf("context free ret = %d\n", ret);
}
