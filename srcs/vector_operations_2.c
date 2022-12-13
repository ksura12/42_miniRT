#include	"../header/minirt.h"

t_vec	vector_dev(t_vec u, t_vec v)
{
	t_vec	ret;

	ret.x = u.x - v.x;
	ret.y = u.y - v.y;
	ret.z = u.z - v.z;
	return (ret);
}
t_vec	vector_rot_x(t_vec v, double alpha)
{
	t_vec	rot;

	rot.x = v.x;
	rot.y = v.y * cos(alpha) - v.z * sin(alpha);
	rot.z = v.y * sin(alpha) + v.z * cos(alpha);
	return (rot);
}

t_vec	vector_rot_y(t_vec v, double alpha)
{
	t_vec	rot;

	rot.x = v.x * cos(alpha) + v.z * sin(alpha);
	rot.y = v.y;
	rot.z = -v.x * sin(alpha) + v.z * cos(alpha);
	return (rot);
}

t_vec	vector_rot_z(t_vec v, double alpha)
{
	t_vec	rot;

	rot.x = v.x * cos(alpha) - v.y * sin(alpha);
	rot.y = v.x * sin(alpha) + v.y * cos(alpha);
	rot.z = v.z;
	return (rot);
}