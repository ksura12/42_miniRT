#include	"../header/minirt.h"

double	degtorad(double deg)
{
	return(deg * M_PI / 180);
}

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
	rot.y = v.y * cos(degtorad(alpha)) - v.z * sin(degtorad(alpha));
	rot.z = v.y * sin(degtorad(alpha)) + v.z * cos(degtorad(alpha));
	return (rot);
}

t_vec	vector_rot_y(t_vec v, double alpha)
{
	t_vec	rot;

	rot.x = v.x * cos(degtorad(alpha)) + v.z * sin(degtorad(alpha));
	rot.y = v.y;
	rot.z = -v.x * sin(degtorad(alpha)) + v.z * cos(degtorad(alpha));
	return (rot);
}

t_vec	vector_rot_z(t_vec v, double alpha)
{
	t_vec	rot;

	rot.x = v.x * cos(degtorad(alpha)) - v.y * sin(degtorad(alpha));
	rot.y = v.x * sin(degtorad(alpha)) + v.y * cos(degtorad(alpha));
	rot.z = v.z;
	return (rot);
}

double	**make_mat44(t_vec forward, t_vec up, t_vec right, t_data *data)
{
	int i;
	i = 0;
	double **ctw;
	ctw = malloc(sizeof(double) * 4);
	while(i < 4)
	{
		ctw[i] = malloc(sizeof(double) * 4);
		i++;
	}

	ctw[0][0] = right.x;
	ctw[0][1] = right.y;
	ctw[0][2] = right.z;
	ctw[0][3] = 0;
	ctw[1][0] = up.x;
	ctw[1][1] = up.y;
	ctw[1][2] = up.z;
	ctw[1][3] = 0;
	ctw[2][0] = forward.x;
	ctw[2][1] = forward.y;
	ctw[2][2] = forward.z;
	ctw[2][3] = 0;
	ctw[3][0] = data->elements->camera->v_pos.x;
	ctw[3][1] = data->elements->camera->v_pos.y;
	ctw[3][2] = data->elements->camera->v_pos.z;
	ctw[3][3] = 1;
	return (ctw);
}

t_vec	mult_vec_mat(t_vec vec, double **mat)
{
	t_vec	ret;

	ret.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0] + mat[3][0];
	ret.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1] + mat[3][1];
	ret.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2] + mat[3][2];
	ret.f = 1;
	return (ret);
}