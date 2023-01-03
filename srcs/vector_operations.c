#include	"../header/minirt.h"

t_vec	make_vector(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	normalise(t_vec vector)
{
	t_vec	v;

	v.x = vector.x / vector_len(vector);
	v.y = vector.y / vector_len(vector);
	v.z = vector.z / vector_len(vector);
	return (v);
}

double	dot_prod(t_vec v1, t_vec v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double	vector_lensqr(t_vec v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double	vector_len(t_vec v)
{
	return (sqrtf(vector_lensqr(v)));
}

t_vec	cross_prod(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vec	vec_mult(t_vec v, double a)
{
	t_vec	ret;

	ret.x = v.x * a;
	ret.y = v.y * a;
	ret.z = v.z * a;
	return (ret);
}
