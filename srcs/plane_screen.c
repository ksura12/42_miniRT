#include	"../header/minirt.h"

t_vec	get_point_of_intersection(double t, t_ray ray);

t_ray	ray_creation_plane_screen(int px, int py, t_data *data, double scale)
{
	double	x;
	double	y;
	t_ray	ray;

	x = (2 * (px + 0.5) / (float)WIDTH -1) * ASPECT_RATIO * scale;
	y = (1 - 2 * (py + 0.5) / (float)HEIGHT) * scale;
	ray.v_direct = make_vector(x, y, 1);
	ray.v_direct = mult_vec_mat(ray.v_direct, \
		data->elements->camera->camtoworld);
	ray.v_direct = normalise(ray.v_direct);
	ray.v_direct = make_opposite_vector(ray.v_direct);
	ray.v_pos = data->elements->camera->v_pos;
	ray.tmax = RAY_T_MAX;
	ray.cy_cap = 8;
	return (ray);
}

void	obj_to_world_mat(t_vec c_orient, double ***mat, t_vec *pos)
{
	t_vec	forward;
	t_vec	right;
	t_vec	up_old;
	t_vec	up_new;

	up_old.x = 0;
	up_old.y = -1;
	up_old.z = 0;
	up_old.f = 0;
	forward = c_orient;
	forward.f = 0;
	right = cross_prod(up_old, forward);
	right = normalise(right);
	right.f = 0;
	up_new = cross_prod(forward, right);
	up_new.f = 0;
	*mat = make_mat44(forward, up_new, right, pos);
	return ;
}

double	**make_mat44(t_vec forward, t_vec up, t_vec right, t_vec *pos)
{
	int		i;
	double	**ctw;

	i = 0;
	ctw = malloc(sizeof(double) * 4);
	while (i < 4)
		ctw[i++] = malloc(sizeof(double) * 4);
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
	ctw[3][0] = pos->x;
	ctw[3][1] = pos->y;
	ctw[3][2] = pos->z;
	ctw[3][3] = 1;
	return (ctw);
}

/**
 * @brief checks if intersection point of ray is in the 
 * shadow of smth (visible without ambient light)
	// printf("direct x : %f\n", shadow_ray.v_direct.x);
	// printf("direct y : %f\n", shadow_ray.v_direct.y);
	// printf("direct z : %f\n", shadow_ray.v_direct.z);
	// printf("lensq: %f\n", vector_lensqr(ray->v_direct));
	// - position of intersection + position of light source
 * @param ray original camera ray
 * @param data 
 * @return int returns 1 if its in the shadow of smth, 0 if its not
 */
int	shadow_rays(t_ray *ray, t_data *data)
{
	t_ray	shadow_ray;
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
//	if (ray->cy_cap == 1)
//		ray->cy_cap = 2;
	shadow_ray.v_pos = get_point_of_intersection(ray->tmax, *ray);
	shadow_ray.v_direct = vector_dev(data->elements->light->v_pos, \
		shadow_ray.v_pos);
	shadow_ray.v_direct = normalise(shadow_ray.v_direct);
	shadow_ray.tmax = RAY_T_MAX;
	while (i < data->counter->create_count)
	{
		if (data->elements->objects[i]->intersection_shadow(&shadow_ray, \
			data, i, &tmp) == 1)
			return (1);
		i++;
	}
	return (0);
}

t_vec	get_point_of_intersection(double t, t_ray ray)
{
	t_vec	intersection;

	intersection.x = ray.v_pos.x + t * ray.v_direct.x;
	intersection.y = ray.v_pos.y + t * ray.v_direct.y;
	intersection.z = ray.v_pos.z + t * ray.v_direct.z;
	return (intersection);
}
