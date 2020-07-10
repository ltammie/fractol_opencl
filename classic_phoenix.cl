static float 	map(float value, float fmin, float fmax, float tmin, float tmax)
{
	return ((value - fmin) * (tmax - tmin) / (fmax - fmin) + tmin);
}

__kernel void array_add(int max_iter, float minX, float maxX, float minY, float maxY, __global float *output)
{
	int x = get_global_id(0);
    int y = get_global_id(1);
    int width = get_global_size(0);
    int height = get_global_size(1);
    int i = 0;

    float2 z;
  	float2 z_prev;
  	float2 c_im_z;
  	float2 c_re, c_im;

   	z = (float2)(map((float)x, 0, width - 1, minX, maxX), map((float)y, 0, height - 1, minY, maxY));
   	z_prev = z;
   	c_re = (float2)(0.5667, 0.0);
   	c_im = (float2)(0.0, -0.5);
    while (i < max_iter)
    {
        z = (float2)(z.x * z.x - (z.y * z.y), z.y * z.x + z.x * z.y);

        c_im_z = (float2)(z_prev.x * c_im.x - (z_prev.y * c_im.y), z_prev.x * c_im.y + z_prev.y * c_im.x);

        z = z + c_re + c_im_z;

        z_prev = z;

    	if (dot(z,z) > 20.0)
    		break;
    	i++;
    }
    if (i == max_iter)
    	output[y * width + x] = i;
    else
    	output[y * width + x] = i - (log2(log2(dot(z,z)))) + 20.0;
}
