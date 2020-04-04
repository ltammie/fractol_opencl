static float 	map(float value, float fmin, float fmax, float tmin, float tmax)
{
	return ((value - fmin) * (tmax - tmin) / (fmax - fmin) + tmin);
}

__kernel void array_add(int	max_iterations, __global int *output)
{
	int x = get_global_id(1);
	int y = get_global_id(0);
	int width = get_global_size(1);
}



/*
__kernel void array_add(__global int *output)
{
	int y = get_global_id(0);
	int x = get_global_id(1);
	int size = get_global_size(1);
	output[y * size + x] = y;
}
*/
