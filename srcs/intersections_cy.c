/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:25:01 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 14:01:28 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

static void	abc_calc(t_ray *ray, t_data *data, int i, float abc[3])
{
	t_vec	w;
	t_obj	*object;

	object = data->elements->objects[i];
	abc[0] = dot_prod(ray->v_direct, ray->v_direct) \
		- powf(dot_prod(ray->v_direct, object->v_orient), 2);
	w = vector_dev(ray->v_pos, object->v_pos);
	abc[1] = 2 * (dot_prod(ray->v_direct, w) - dot_prod(ray->v_direct, \
		object->v_orient) * dot_prod(w, object->v_orient));
	abc[2] = dot_prod(w, w) - powf(dot_prod(w, object->v_orient), 2) \
		- powf(object->dia / 2, 2);
}

float	does_intersect_cy_disk(t_ray *ray, t_data *data, int i, int disk, int *objid)
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
