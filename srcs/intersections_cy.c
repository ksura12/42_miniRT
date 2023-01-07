/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:25:01 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 17:25:04 by kaheinz          ###   ########.fr       */
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

float	intersect_cy_disk(t_ray *ray, t_data *data, int util[], int *objid)
{
	float	den[2];
	t_vec	inters[2];
	t_obj	*cy;

	cy = data->elements->objects[util[0]];
	den[0] = dot_prod(ray->v_direct, cy->v_orient);
	if (!isequal(den[0], 0))
	{
		den[1] = dot_prod(cy->v_orient, vector_dev(vec_add(cy->v_pos, vec_mult \
			(cy->v_orient, cy->height * util[1])), ray->v_pos)) / den[0];
		if (islessequal(den[1], 0))
			return (-1);
		inters[0] = vec_add(ray->v_pos, vec_mult(ray->v_direct, den[1]));
		inters[1] = vector_dev(inters[0], vec_add(cy->v_pos, \
			vec_mult(cy->v_orient, cy->height * util[1])));
		if (sqrtf(dot_prod(inters[1], inters[1])) < (cy->dia / 2)
			&& (den[1] < ray->tmax || ray->tmax < 0))
		{
			ray->tmax = den[1];
			*objid = util[0];
			ray->cy_cap = 1;
			return (den[1]);
		}
	}
	return (-1);
}

int	does_intersect_cy_shadow(t_ray *ray, t_data *data, int i, int *objid)
{
	float	tmp[3];
	float	abc[3];

	tmp[0] = disks(ray, data, i, objid);
	abc_calc(ray, data, i, abc);
	if (islessequal(pow(abc[1], 2) - 4.0 * abc[0] * abc[2], 0) && tmp[0] < 0)
		return (-1);
	if (ray->cy_cap == 1)
		return (check(ray, data));
	tmp[2] = quad_solver(abc[0], abc[1], abc[2]);
	if ((tmp[0] > 0 && tmp[0] < tmp[2]) || tmp[2] < 0)
		return (-1);
	else if (isgreaterequal(tmp[2], 0))
	{
		tmp[1] = precheck(ray, tmp, data, i);
		if (isgreaterequal(tmp[1], 0) && isless(tmp[2], ray->tmax)
			&& islessequal(tmp[1], data->elements->objects[i]->height))
		{
			inter_found(i, objid, ray, tmp[2]);
			return (check(ray, data));
		}
	}
	return (0);
}

int	does_intersect_cy(t_ray *ray, t_data *data, int i, int *objid)
{
	float	tmp[2];
	float	abc[3];
	float	ret;

	tmp[0] = disks(ray, data, i, objid);
	abc_calc(ray, data, i, abc);
	if (islessequal(pow(abc[1], 2) - 4.0 * abc[0] * abc[2], 0) && tmp[0] < 0)
		return (-1);
	ret = quad_solver(abc[0], abc[1], abc[2]);
	if ((tmp[0] > 0 && tmp[0] < ret) || ret < 0)
		return (-1);
	else if (isgreaterequal(ret, 0))
	{
		tmp[1] = dot_prod(vector_dev(vec_add(ray->v_pos, \
			vec_mult(ray->v_direct, ret)), data->elements->objects[i]->v_pos), \
			data->elements->objects[i]->v_orient);
		if (isgreaterequal(tmp[1], 0) && isless(ret, ray->tmax)
			&& islessequal(tmp[1], data->elements->objects[i]->height))
		{
			inter_found(i, objid, ray, ret);
			return (tmp[0] || tmp[1]);
		}
	}
	return (-1);
}
