static float 	map(float value, float fmin, float fmax, float tmin, float tmax)
{
	return ((value - fmin) * (tmax - tmin) / (fmax - fmin) + tmin);
}

static	float2	comp_mult(float2 a, float2 b)
{
	float2 res = (float2)(0.0, 0.0);

    res.x = (a.x * b.x - a.y * b.y);
    res.y = (a.x * b.y + a.y * b.x);
    return (res);
}

__kernel void array_add(int max_iter, float min_x, float max_x, float min_y, float max_y,  __global float *output,
										float re, float im)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);
	int i = 0;

	float2 z, c;
	z.x = map((float)x, 0, width - 1, min_x, max_x);
	z.y = map((float)y, 0, height - 1, min_y, max_y);
	c = (float2)(re, im);
	while (i < max_iter)
	{
		z = comp_mult(z,z) + c;
		if (dot(z,z) > 10)
			break;
		i++;
	}
	if (i == max_iter)
    	output[y * width + x] = i;
    else
    	output[y * width + x] = i - (log2(log2(dot(z,z)))) + 10.0;
}
