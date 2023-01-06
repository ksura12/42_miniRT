#include	"../header/minirt.h"


void	set_tmax_shadow(t_data *data, t_ray *ray, double t)
{
	if(!vec_comp(ray->v_pos, data->elements->light->v_pos))
		ray->tmax = vector_len(vector_dev(get_point_of_intersection(t, *ray), data->elements->light->v_pos));
}
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
		return (0);
	w = vector_dev(plane->v_pos, ray->v_pos);
	t = dot_prod(plane->v_orient, w) / ndotray;
	// set_tmax_shadow(data, ray, t);
	if (t <= RAY_T_MIN || t >= ray->tmax)
	{
		return (0);
	}
		
	*objid = i;
	ray->tmax = t;
	// if (!vec_comp(ray->v_pos, data->elements->light->v_pos) && t < 0)
	// 	return (0);
	if (t > vector_len(vector_dev(data->elements->light->v_pos, ray->v_pos)))
		return (0);
	// if (vector_len(vector_dev(ray->v_pos, data->elements->light->v_pos)) \ 	< vector_len(vector_dev(ray->v_pos, \	get_point_of_intersection(ray->tmax, *ray))))
	// 	return (0);
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

void	abc_calc(t_ray *ray, t_data *data, int i, float abc[3])
{
	t_vec	w;

	abc[0] = dot_prod(ray->v_direct, ray->v_direct) \
		- powf(dot_prod(ray->v_direct, data->elements->objects[i]->v_orient), 2);
	w = vector_dev(ray->v_pos, data->elements->objects[i]->v_pos);
	abc[1] = 2 * (dot_prod(ray->v_direct, w) - dot_prod(ray->v_direct, \
		data->elements->objects[i]->v_orient) * dot_prod(w, data->elements->objects[i]->v_orient));
	abc[2] = dot_prod(w ,w) - powf(dot_prod(w, data->elements->objects[i]->v_orient), 2) \
		- powf(data->elements->objects[i]->dia / 2, 2);
}

int	isequal(float a, float b)
{
	return ((a - 0.00001 <= b) && (a + 0.00001 >= b));
}

float does_intersect_cy_disk(t_ray *ray, t_data *data, int i, int disk, int *objid)
{
	float	den;
	float	t;
	t_vec	inters;
	t_vec	v;
	t_obj	*cy;

	cy = data->elements->objects[i];
	den = dot_prod(ray->v_direct, cy->v_orient);
	if (!isequal(den, 0))
	{
		t = dot_prod(cy->v_orient, vector_dev(vec_add(cy->v_pos, \
			vec_mult(cy->v_orient, cy->height * disk)), ray->v_pos)) / den;
		if (islessequal(t, 0))
			return (-1);
		inters = vec_add(ray->v_pos, vec_mult(ray->v_direct, t));
		v = vector_dev(inters, vec_add(cy->v_pos, vec_mult(cy->v_orient, \
			cy->height * disk)));
		if (sqrtf(dot_prod(v, v)) < (cy->dia / 2) && (t < ray->tmax || ray->tmax < 0))
		{
			ray->tmax = t;
			*objid = i;
			ray->cy_cap = 1;
			return (t);
		}
	}
	return (-1);
}

float	find_min_value(float a, float b)
{
	if ((isless(a, b) && isgreater(a, 0)) || (a == b))
	{
		return (a);
	}
	else if ((b < a) && (b > 0))
	{
		return (b);
	}
	else
		return (-1);
}

float	quad_solver(float a, float b, float c)
{
	float	delta;
	float	t[2];

	delta = b * b - 4 * (a * c);
	if (fabs(delta) < EPSILON)
		return (0);
	if (delta < 0)
		return (0);
	t[0] = (-b - sqrt(delta)) / ( 2 * a);
	t[1] = (-b + sqrt(delta)) / ( 2 * a);
	return (find_min_value(t[0], t[1]));
}

int	does_intersect_cy_shadow(t_ray *ray, t_data *data, int i, int *objid)
{
	float	tmp[2];
	float	abc[3];
	float	ret;

	tmp[0] = find_min_value(does_intersect_cy_disk(ray, data, i, 0, objid), \
		does_intersect_cy_disk(ray, data, i, 1, objid));
	abc_calc(ray, data, i, abc);
	if (islessequal(pow(abc[1], 2) - 4.0 * abc[0] * abc[2], 0) && tmp[0] < 0)
		return(-1);
	if (ray->cy_cap == 1 && ray->tmax <= vector_len(vector_dev(data->elements->light->v_pos, ray->v_pos)))
		return (1);
	else if (ray->cy_cap == 1 && ray->tmax > vector_len(vector_dev(data->elements->light->v_pos, ray->v_pos)))
		return (0);
	ret = quad_solver(abc[0], abc[1], abc[2]);
	if ((tmp[0] > 0 && tmp[0] < ret) || ret < 0)
		return (-1);
	else if (isgreaterequal(ret, 0))
	{
		tmp[1] = dot_prod(vector_dev(vec_add(ray->v_pos, vec_mult(ray->v_direct, ret))\
			, data->elements->objects[i]->v_pos), data->elements->objects[i]->v_orient);
		if (isgreaterequal(tmp[1], 0) && islessequal(tmp[1], data->elements->objects[i]->height))
		{
			*objid = i;
			ray->tmax = ret;
			ray->cy_cap = 0;
			if (ray->tmax > vector_len(vector_dev(data->elements->light->v_pos, ray->v_pos)))
				return (0);
			else
				return (1);
		}
	}
	return (0);
}

int	does_intersect_cy(t_ray *ray, t_data *data, int i, int *objid)
{
	float	tmp[2];
	float	abc[3];
	float	ret;

	tmp[0] = find_min_value(does_intersect_cy_disk(ray, data, i, 0, objid), \
		does_intersect_cy_disk(ray, data, i, 1, objid));
	abc_calc(ray, data, i, abc);
	if (islessequal(pow(abc[1], 2) - 4.0 * abc[0] * abc[2], 0) && tmp[0] < 0)
		return (-1);
	ret = quad_solver(abc[0], abc[1], abc[2]);
	if ((tmp[0] > 0 && tmp[0] < ret) || ret < 0)
		return (-1);
	else if (isgreaterequal(ret, 0))
	{
		tmp[1] = dot_prod(vector_dev(vec_add(ray->v_pos, vec_mult(ray->v_direct, ret))\
			, data->elements->objects[i]->v_pos), data->elements->objects[i]->v_orient);
		if (isgreaterequal(tmp[1], 0) && islessequal(tmp[1], data->elements->objects[i]->height))
		{
			*objid = i;
			ray->tmax = ret;
			ray->cy_cap = 0;
			return (tmp[0] || tmp[1]);
		}
	}
	return (-1);
}

	// double	t[2];
	// t_vec	w;
	// int		ret;

	// ret = 0;


	// delta = b * b - 4 * (a * c);
	// if (fabs(delta) < EPSILON)
	// 	return (0);
	// if (delta < 0)
	// 	return (0);

	// t[0] = (-b - sqrt(delta)) / ( 2 * a);
	// if (t[0] > RAY_T_MIN && t[0] < ray->tmax)
	// {
	// 	r = ray->v_pos.y + t[0] * ray->v_direct.y;
	// 	if (r >= data->elements->objects[i]->v_pos.y && r <= data->elements->objects[i]->v_pos.y + data->elements->objects[i]->height)
	// 	{
	// 		ray->tmax = t[0];
	// 		ret = 1;
	// 		*objid = i;
	// 	}
	// }
	// t[1] = (-b + sqrt(delta)) / ( 2 * a);
	// if (t[1] > RAY_T_MIN && t[1] < ray->tmax)
	// {
	// 	r = ray->v_pos.y + t[1] * ray->v_direct.y;
	// 	if (r >= data->elements->objects[i]->v_pos.y && r <= data->elements->objects[i]->v_pos.y + data->elements->objects[i]->height)
	// 	{
	// 		ray->tmax = t[1];
	// 		ret = 1;
	// 		*objid = i;
	// 	}
	// }
	// return (ret);

	



// float Cylinder::intersect(Vector pos, Vector dir)
// {   
//     float a = (dir.x * dir.x) + (dir.z * dir.z);
//     float b = 2*(dir.x*(pos.x-center.x) + dir.z*(pos.z-center.z));
//     float c = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z) - (radius*radius);
    
//     float delta = b*b - 4*(a*c);
// 	if(fabs(delta) < 0.001) return -1.0; 
//     if(delta < 0.0) return -1.0;
    
//     float t1 = (-b - sqrt(delta))/(2*a);
//     float t2 = (-b + sqrt(delta))/(2*a);
//     float t;
    
//     if (t1>t2) t = t2;
//     else t = t1;
    
//     float r = pos.y + t*dir.y;
    
//     if ((r >= center.y) and (r <= center.y + height))return t;
//     else return -1;
// }

// /**
// * Returns the unit normal vector at a given point.
// * Assumption: The input point p lies on the sphere.
// */
// Vector Cylinder::normal(Vector p)
// {
//     Vector n = Vector (p.x-center.x,0,p.z-center.z);
//     n.normalise();
//     return n;
// }
// }
