#include	"../header/minirt.h"

/**
 * @brief returns 1 of it intersects with scene, 0 if not
 * 
 */
//	printf("ndotray: %f\n", ndotray);
//	printf("return epsilon\n");
//	printf("t: %f\n", t);
int	does_intersect_p(t_ray *ray, t_data *data, int i, int *objid)
{
	t_obj	*plane;
	double	ndotray;
	double	t;
	t_vec	w;

	plane = data->elements->objects[i];
	ndotray = dot_prod(plane->v_orient, ray->v_direct);
	if (fabs(ndotray) < EPSILON)
	{
		return (0);
	}
	w = vector_dev(plane->v_pos, ray->v_pos);
	t = dot_prod(plane->v_orient, w) / ndotray;
	if (t <= RAY_T_MIN || t >= ray->tmax)
		return (0);
	*objid = i;
	ray->tmax = t;
	// if (!vec_comp(ray->v_pos, data->elements->light->v_pos) && t < 0)
	// 	return (0);
	if (t > vector_len(vector_dev(data->elements->light->v_pos, ray->v_pos)))
		return (0);
	return (1);
}

/**
 * @brief returns 1 of it intersects with scene, 0 if not
	// Transform ray so we can consider origin-centred sphere
	// Calculate quadratic coefficients
	// abc[0] = dot_prod(ray->v_direct, make_vector(0,0,0));
	// c = dot_prod(pos_new, make_vector(0,0,0)) - 
	// pow((data->elements->objects[i]->dia / 2), 2);
	// Check whether we intersect
	// Find two points of intersection, t1 close and t2 far
		// printf("ray.t0 = %f\n", t[0]);
		// printf("ray.tmax = %f\n",ray->tmax);
		// printf("ray. objid %i was hit\n", *objid);
	// printf("init ray t[0]: %f\n", t[0]);
 * 
 */
int	does_intersect_s(t_ray *ray, t_data *data, int i, int *objid)
{
	double	abc[3];
	t_vec	pos_new;
	double	discriminant;
	double	t[2];
	int		ret;

	pos_new = vector_dev(ray->v_pos, data->elements->objects[i]->v_pos);
	abc[0] = vector_lensqr(ray->v_direct);
	abc[1] = 2 * dot_prod(ray->v_direct, pos_new);
	abc[2] = vector_lensqr(pos_new) - pow((data->elements->objects[i]->dia 
		/ 2), 2);
	discriminant = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return (0);
	t[0] = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	// if (!vec_comp(ray->v_pos, data->elements->light->v_pos) && t[0] < 0)
	// 	return (0);
	ret = 0;
	if (t[0] > (float)RAY_T_MIN && t[0] < ray->tmax)
	{
		ray->tmax = t[0];
		ret = 1;
		*objid = i;
	}
	t[1] = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	if (t[1] > (float)RAY_T_MIN && t[1] < ray->tmax)
	{
		ray->tmax = t[1];
		ret = 1;
		*objid = i;
	}
	if (vector_len(vector_dev(ray->v_pos, data->elements->light->v_pos)) \
		< vector_len(vector_dev(ray->v_pos, \
		get_point_of_intersection(ray->tmax, *ray))))
		ret = 0;
	return (ret);
}

int	does_intersect_cy(t_ray *ray, t_data *data, int i, int *objid)
{
	(void) ray;
	(void) data;
	(void) i;
	(void) objid;
	return (1);
}
