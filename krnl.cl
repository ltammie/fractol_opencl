static float 	map(float value, float fmin, float fmax, float tmin, float tmax)
{
	return ((value - fmin) * (tmax - tmin) / (fmax - fmin) + tmin);
}

__kernel void array_add(int max_iter, __global float *output)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	int i = 0;

	float2 c, z;

	z.x = 0.0f;
	z.y = 0.0f;
	c.x = map((float)x, 0.0f, 1280.0f, -2.0f, 2.0f);
	c.y = map((float)y, 0.0f, 720.0f, -2.0f, 1.0f);
	while (i < max_iter)
	{
		float tx = (z.x * z.x - z.y * z.y) + c.x;
		float ty = (z.y * z.x + z.x * z.y) + c.y;
        if((tx * tx + ty * ty) > 4.0)
        	break;
        z.x = tx;
        z.y = ty;
		i++;
	}
	output[x][y] = i;
}
