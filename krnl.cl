__kernel void array_add(__global float *output)
{
	int y = get_global_id(0);
	int x = get_global_id(1);
	int g = get_global_size(1);

	float2 v1, v2;
	v1 = (float2)(1.0, 2.0);
	v2 = (float2)(3.0, 4.0);
	v1 = v1 * v1 + v2;
	output[y * g + x] = v1.y;
}
