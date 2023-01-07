/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:25:13 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 05:37:28 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

void	surface_normal_s(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	(void) ray;
	shadow->i_normal = vector_dev(shadow->intersection, \
		data->elements->objects[*objid]->v_pos);
	shadow->i_normal = normalise(shadow->i_normal);
}

void	surface_normal_p(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	(void) ray;
	shadow->i_normal = vec_mult(data->elements->objects[*objid]->v_orient, 1);
}

void	surface_normal_c(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	double	t;
	t_vec	pt;
	t_obj	*cylinder;

	cylinder = data->elements->objects[*objid];
	if (ray->cy_cap == 1)
		shadow->i_normal = cylinder->v_orient;
	else
	{
		t = dot_prod(vector_dev(shadow->intersection, cylinder->v_pos), \
			cylinder->v_orient);
		pt = vec_add(cylinder->v_pos, vec_mult(cylinder->v_orient, t));
		shadow->i_normal = normalise(vector_dev(shadow->intersection, pt));
	}
}
