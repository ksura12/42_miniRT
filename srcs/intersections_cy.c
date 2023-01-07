/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:25:01 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 11:22:26 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

static void	abc_calc(t_ray *ray, t_data *data, int i, float abc[3])
{
	t_vec	w;
	t_obj	*obj;

	obj = data->elements->objects[i];
	abc[0] = dot_prod(ray->v_direct, ray->v_direct) \
		- powf(dot_prod(ray->v_direct, obj->v_orient), 2);
	w = vector_dev(ray->v_pos, obj->v_pos);
	abc[1] = 2 * (dot_prod(ray->v_direct, w) - dot_prod(ray->v_direct, \
		obj->v_orient) * dot_prod(w, obj->v_orient));
	abc[2] = dot_prod(w, w) - powf(dot_prod(w, obj->v_orient), 2) \
		- powf(obj->dia / 2, 2);
}

/**
 * @brief checks if ray intersect with a cap of cylinder
 * 
 * 
 * @param ray 
 * @param data 
 * @param io int * with io[0] = i and io[1] = objid
 * @param disk 0 for lower cap, 1 for upper cap
 * @return [float] t value if intersect, -1 if not
 */
float	does_intersect_cy_disk(t_ray *ray, t_data *data, int *io, int disk)
{
	float	den;
	float	t;
	t_vec	inters;
	t_vec	v;
	t_obj	*cy;

	cy = data->elements->objects[io[0]];
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
		if (sqrtf(dot_prod(v, v)) < (cy->dia / 2) && (t < ray->tmax \
			|| ray->tmax < 0))
		{
			ray->tmax = t;
			io[1] = io[0];
			ray->cy_cap = 1;
			return (t);
		}
	}
	return (-1);
}

int	does_intersect_cy_shadow(t_ray *ray, t_data *data, int i, int *objid)
{
	float	tmp[2];
	float	abc[3];
	float	ret;
	int		*io;

	io = malloc(sizeof(int *));
	io[0] = i;
	io[1] = *objid;
	tmp[0] = find_min_value(does_intersect_cy_disk(ray, data, io, 0), \
		does_intersect_cy_disk(ray, data, io, 1));
	free(io);
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
	int		*io;

	io = malloc(sizeof(int *) * 2);
	io[0] = i;
	io[1] = *objid;

	tmp[0] = find_min_value(does_intersect_cy_disk(ray, data, io, 0), \
		does_intersect_cy_disk(ray, data, io, 1));
	free(io);
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
