/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:25:01 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 10:28:27 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

void	set_tmax_shadow(t_data *data, t_ray *ray, double t)
{
	if (!vec_comp(ray->v_pos, data->elements->light->v_pos))
		ray->tmax = vector_len(vector_dev(get_point_of_intersection(t, *ray), \
			data->elements->light->v_pos));
}

/**
 * @brief returns 1 of it intersects with scene, 0 if not
 * 
 */
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
	if (t <= RAY_T_MIN || t >= ray->tmax)
	{
		return (0);
	}
	*objid = i;
	ray->tmax = t;
	if (t > vector_len(vector_dev(data->elements->light->v_pos, ray->v_pos)))
		return (0);
	return (1);
}

/**
 * @brief checks that the shadow is not behind light source
 * 
 * @param data 
 * @param ray 
 * @param ret 
 */
static void	shadow_direct(t_data *data, t_ray *ray, int *ret)
{
	if (vector_len(vector_dev(ray->v_pos, data->elements->light->v_pos)) \
		< vector_len(vector_dev(ray->v_pos, \
		get_point_of_intersection(ray->tmax, *ray))))
		*ret = 0;
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
	double	tt;
	int		ret;

	pos_new = vector_dev(ray->v_pos, data->elements->objects[i]->v_pos);
	abc[0] = vector_lensqr(ray->v_direct);
	abc[1] = 2 * dot_prod(ray->v_direct, pos_new);
	abc[2] = vector_lensqr(pos_new) - pow((data->elements->objects[i]->dia \
	/ 2), 2);
	discriminant = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return (0);
	tt = quad_solver(abc[0], abc[1], abc[2]);
	ret = 0;
	if (tt > (float)RAY_T_MIN && tt < ray->tmax)
	{
		ray->tmax = tt;
		ret = 1;
		*objid = i;
	}
	shadow_direct(data, ray, &ret);
	return (ret);
}
