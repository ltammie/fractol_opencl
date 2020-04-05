static float 	map(float value, float fmin, float fmax, float tmin, float tmax)
{
	return ((value - fmin) * (tmax - tmin) / (fmax - fmin) + tmin);
}

__kernel void array_add(int max_iter, float minX, float maxX, float minY, float maxY, __global int *output)
{
	int y = get_global_id(0);
	int x = get_global_id(1);
	int width = get_global_size(1);
	int height = get_global_size(0);
	int i = 0;

	float2 z, c;
	z = (float2)(0.0, 0.0);
	c.x = map((float)x, 0, width - 1, minX, maxX);
	c.y = map((float)y, 0, height - 1, minY, maxY);
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
	output[y * width + x] = i;
}
