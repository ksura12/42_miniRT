#include	"../header/minirt.h"

int	ray_create(t_data *data, t_ray *ray, int px, int py)
{
	t_coord	coord;
	t_vec	cam;
	t_vec	dir;

	cam = data->elements->camera->v_orient;
	coord = conversion(px, py);
	ray->tmax = RAY_T_MAX;
	ray->v_pos = data->elements->camera->v_pos;
	if(cam.y == 0 && cam.z == 0)
	{
		dir = vector_rot_z(cam, coord.y * data->elements->camera->angle_vert);
		dir = vector_rot_y(dir, coord.x * data->elements->camera->angle_horz);
		//rotate for pixel row around z and for colum araound y
	}
	if(cam.x == 0 && cam.z == 0)
	{
		dir = vector_rot_x(cam, coord.y * data->elements->camera->angle_vert);
		dir = vector_rot_z(dir, coord.x * data->elements->camera->angle_horz);
		//rotate for pixel row around x and for colum araound z
	}
	else
	{
		dir = vector_rot_x(cam, coord.y * data->elements->camera->angle_vert);
		dir = vector_rot_y(dir, coord.x * data->elements->camera->angle_horz);
		//rotate for pixel row around x and for colum araound y
	}
	ray->v_direct = dir;
	return (1);
}

/**
 * @brief returns 1 of it intersects with scene, 0 if not
 * 
 */
int	does_intersect_p(t_ray ray, t_data *data)
{	
	double raydotn;
	double t;

	raydotn = dot_prod(ray.v_direct, data->elements->objects[0]->v_orient);
	if (raydotn == 0)
		return(0);
	t = dot_prod(vector_dev(data->elements->objects[0]->v_pos, ray.v_pos), data->elements->objects[0]->v_orient) / raydotn;
	if (t <= RAY_T_MIN || t >= ray.tmax)
		return(0);
	return(1);
}

/**
 * @brief returns 1 of it intersects with scene, 0 if not
 * 
 */
int	intersect_p(t_ray ray, t_data *data)
{	
	double raydotn;
	double t;

	raydotn = dot_prod(ray.v_direct, data->elements->objects[0]->v_orient);
	if (raydotn == 0)
		return(0);
	t = dot_prod(vector_dev(data->elements->objects[0]->v_pos, ray.v_pos), data->elements->objects[0]->v_orient) / raydotn;
	if (t <= RAY_T_MIN || t >= ray.tmax)
		return(0);
	ray.tmax = t;
	return(1);
}

