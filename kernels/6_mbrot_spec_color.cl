static float 	map(float value, float fmin, float fmax, float tmin, float tmax)
{
	return ((value - fmin) * (tmax - tmin) / (fmax - fmin) + tmin);
}

static	float2	exponent(float2 n)
{
	float2 res = (float2)(0.0, 0.0);
	res.x = exp(n.x) * cos(n.y);
	res.y = exp(n.x) * sin(n.y);
	return (res);
}

static	float2	comp_div(float2 a, float2 b)
{
	float		div;
	float2 res = (float2)(0.0, 0.0);


	div = (b.x * b.x + b.y * b.y);
	res.x = ((a.x * b.x + a.y * b.y) / div);
	res.y = ((a.y * b.x - a.x * b.y) / div);
	return (res);
}

static	float2	comp_mult(float2 a, float2 b)
{
	float2 res = (float2)(0.0, 0.0);

    res.x = (a.x * b.x - a.y * b.y);
    res.y = (a.x * b.y + a.y * b.x);
    return (res);
}

static float2 comp_pow(float2 a, int n)
{
    float2 tmp = a;
    float2 res = a;

    int i = 1;
    while (i < n)
    {
        res = comp_mult(res, tmp);
        i++;
    }
    return (res);
}

static	int color(int iter, int max, float2 z, float2 d, float ang)
{
	float			reflection = (float)(0.0);
	unsigned int	b;

	float		h = (float)1.3;
	float		angle = (float)(ang / 360.0);
	float2		v = (float2)(0.0, 0.0);
	float2		u = (float2)(0.0, 0.0);
	float2		u_tmp = (float2)(0.0, 0.0);

	v.y = (2 * angle * M_PI_F);
	v = exponent(v);

	if (iter != max)
	{
		u = comp_div(z, d);
		u_tmp.x = length(u);
		u = comp_div(u, u_tmp);
		reflection = dot(u, v);
		reflection = reflection + h;
		reflection = (float)(reflection / (1.0 + h));
	}
	b = (int)(255 * reflection);
	return ((reflection <= 0) ? ((12 << 16) | (5 << 8) | 555) : ((b << 16) | (b << 8) | b));
}

__kernel void array_add(int max_iter, float min_x, float max_x, float min_y, float max_y,__global float *output, int p,
						float angle)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);
	int i = 0;

	float2 z, c, d, two, one;
	z = (float2)(0.0, 0.0);
	d = (float2)(0.0, 0.0);
	two = (float2)(2.0, 0.0);
	one = (float2)(1.0, 0.0);
	c.x = map((float)x, 0, width - 1, min_x, max_x);
	c.y = map((float)y, 0, height - 1, min_y, max_y);
	while (i < max_iter)
	{
		d = comp_mult(two, d);
		d = comp_mult(d, z);
		d = d + one;
		z = comp_pow(z, p) + c;
		if (dot(z,z) > 20.0)
			break;
		i++;
	}
	i = i == max_iter ? i : i - (log2(log2(dot(z,z)))) + 20.0;
	output[y * width + x] = color(i, max_iter, z, d, angle);
}
