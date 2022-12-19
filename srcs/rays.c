#include	"../header/minirt.h"

int	ray_create(t_data *data, t_ray *ray, int px, int py)
{
	t_coord	coord;
	t_vec	cam;
	t_vec	dir;

	cam = data->elements->camera->v_orient;
	coord = conversion(px, py);
	// printf("angel per pixel h: %f\n", data->elements->camera->angle_horz);
	// printf("angel per pixel v: %f\n", data->elements->camera->angle_vert);
	// printf("original x: %i\n", px);
	// printf("new x: %f\n", coord.x);
	// printf("original y: %i\n", py);
	// printf("new y: %f\n", coord.y);
	// printf("angel of rotation h: %f\n", (coord.x * data->elements->camera->angle_horz));
	
	ray->tmax = RAY_T_MAX;
	ray->v_pos = data->elements->camera->v_pos;
	if(cam.y == 0 && cam.z == 0)
	{
		dir = vector_rot_y(cam, coord.x * data->elements->camera->angle_horz);
		dir = vector_rot_x(dir, coord.y * data->elements->camera->angle_vert);
		
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
	if (-t <= RAY_T_MIN)
	{
		printf("heer\n");
		printf("t: %f\n", t);
		printf("t.max: %f\n", ray.tmax);
		return(0);
	}
	if ( -t >= ray.tmax)
	{
		printf("heer1\n");
		printf("t.max: %f\n", ray.tmax);
		printf("t: %f\n", t);
		return(0);
	}
		
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

int does_intersect_s(t_ray *ray, t_data *data, int i, int *objid)
{

	double	a;
	double	b;
	double	c;
	t_vec	pos_new;
	double	discriminant;
	double	t[2];
	int		ret;
	// Transform ray so we can consider origin-centred sphere
	pos_new = vector_dev(ray->v_pos, data->elements->objects[i]->v_pos);
	// Calculate quadratic coefficients
	a = vector_lensqr(ray->v_direct);
	// a = dot_prod(ray->v_direct, make_vector(0,0,0));
	b = 2 * dot_prod(ray->v_direct, pos_new);
	
	c = vector_lensqr(pos_new) - pow((data->elements->objects[i]->dia / 2), 2);
	// c = dot_prod(pos_new, make_vector(0,0,0)) -  pow((data->elements->objects[i]->dia / 2), 2);
	// Check whether we intersect
	discriminant = pow(b, 2) - 4 * a* c;
	if (discriminant < 0.0)
	{
		return (0);
	}
	// Find two points of intersection, t1 close and t2 far
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	ret = 0;
	if (t[0] > (float)RAY_T_MIN && t[0] < ray->tmax)
	{
		ray->tmax = t[0];
		ret = 1;
		*objid = i;
		// printf("ray.t0 = %f\n", t[0]);
		// printf("ray.tmax = %f\n",ray->tmax);
		// printf("ray. objid %i was hit\n", *objid);
	}
	// printf("init ray t[0]: %f\n", t[0]);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	if (t[1] > (float)RAY_T_MIN && t[1] < ray->tmax)
	{
		ray->tmax = t[1];
		ret = 1;
		*objid = i;
	}
	return(ret);


	// t_vec	oc;
	// t_vec	tmp;
	// double	disc;

	// oc = vector_dev(ray->v_pos, data->elements->objects[i]->v_pos);
	// tmp.x = dot_prod(ray->v_direct, NULL);
	// tmp.y = 2.0 * dot_prod(oc, ray->v_direct);
	// tmp.z = dot_prod(oc, NULL) - pow(data->elements->objects[i]->dia / 2, 2);
	// disc = tmp.y * tmp.y - 4 * tmp.x * tmp.z;
	// if (disc < 0)
	// 	return (0);
	// else
	// 	return (-((tmp.y) + sqrt(disc)) / tmp.x);
}

int does_intersect_s_shadow(t_ray *ray, t_data *data)
{
	double a;
	double b;
	double c;
	double discriminant;
	double t[2];
	// Transform ray so we can consider origin-centred sphere
	ray->v_pos = vector_dev(ray->v_pos, data->elements->objects[0]->v_pos);
	// Calculate quadratic coefficients
	a = vector_lensqr(ray->v_direct);
	b = 2 * dot_prod(ray->v_direct, ray->v_pos);
	c = vector_lensqr(ray->v_pos) - pow((data->elements->objects[0]->dia / 2), 2);
	// Check whether we intersect
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0.0)
	{
		return (0);
	}
	// Find two points of intersection, t1 close and t2 far
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	if (t[0] > (float)RAY_T_MIN && t[0] < ray->tmax)
	{
		ray->tmax = t[0];
		return (1);
	}
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	if (t[1] > (float)RAY_T_MIN && t[1] < ray->tmax)
	{
		ray->tmax = t[1];
		return (1);
	}
	return(0);
}
