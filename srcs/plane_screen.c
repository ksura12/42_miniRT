#include	"../header/minirt.h"

t_ray	ray_creation_plane_screen(int px, int py, t_data *data, double scale)
{
	double	x;
	double	y;
	t_ray	ray;
	double	camtoworld[4][4];

	x = (2 * (px + 0.5) / (float)WIDTH -1) * ASPECT_RATIO * scale;
	y = (1- 2 * (py + 0.5) / (float)HEIGHT) * scale;
	ray.v_direct = make_vector(x, y, -1);
	cam_to_world_mat(data->elements->camera->v_orient, camtoworld);
	ray.v_direct = mult_vec_mat(ray.v_direct, camtoworld);
	ray.v_direct = normalise(ray.v_direct);
	ray.v_pos = data->elements->camera->v_pos;
	return (ray);
}


void	cam_to_world_mat(t_vec c_orient, double **mat)
{
	t_vec	forward;
	t_vec	right;
	t_vec	up_old;
	t_vec	up_new;

	up_old.x = 0;
	up_old.y = 1;
	up_old.z = 0;
	up_old.f = 0;
	forward = c_orient;
	forward.f = 0;
	right = cross_prod(up_old, forward);
	right = normalise(right);
	right.f = 0;
	up_new = cross_prod(forward, right);
	up_new.f = 0;
	make_mat44(forward, up_new, right, mat);
	return ;
}	