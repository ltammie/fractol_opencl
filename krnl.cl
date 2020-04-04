static float 	map(float value, float fmin, float fmax, float tmin, float tmax)
{
	return ((value - fmin) * (tmax - tmin) / (fmax - fmin) + tmin);
}

__kernel void array_add(int max_iter, int min_value, int max_value, __global int *output)
{
	int y = get_global_id(0);
	int x = get_global_id(1);
	int width = get_global_size(1);
	int height = get_global_size(0);
	int i = 0;

	float2 z, c;
	z = (float2)(0.0, 0.0);
	c.x = map((float)x, 0, width - 1, min_value, max_value);
	c.y = map((float)y, 0, height - 1, min_value, max_value);
	while (i < max_iter)
	{

		float2 tmp;

        tmp.x = z.x * z.x + (-1) * (z.y * z.y);
        tmp.y = z.y * z.x + z.x * z.y;
		z = tmp + c;
		if ((z.x * z.x + z.y * z.y) > 4)
			break;
		i++;
	}
	if (i < max_iter)
		output[y * width + x] = 0xff0000;
	else
		output[y * width + x] = 0x000000;
}
