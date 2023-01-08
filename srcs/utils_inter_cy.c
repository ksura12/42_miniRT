/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_inter_cy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:25:01 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 17:49:52 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

int	check(t_ray *ray, t_data *data)
{
	t_light	*light;

	light = data->elements->light;
	if (ray->tmax > vector_len(vector_dev(light->v_pos, ray->v_pos)))
		return (0);
	else
		return (1);
}

void	inter_found(int i, int *objid, t_ray *ray, float ret)
{
	*objid = i;
	ray->tmax = ret;
	ray->cy_cap = 2;
}

float	precheck(t_ray *ray, float tmp[], t_data *data, int i)
{
	t_obj	*object;

	object = data->elements->objects[i];
	tmp[1] = dot_prod(vector_dev(vec_add(ray->v_pos, \
		vec_mult(ray->v_direct, tmp[2])), object->v_pos), object->v_orient);
	return (tmp[1]);
}

float	disks(t_ray *ray, t_data *data, int i, int *objid)
{
	int		util[2];
	float	disks[2];
	float	tmp;

	util[0] = i;
	util[1] = 0;
	disks[0] = intersect_cy_disk(ray, data, util, objid);
	util[1] = 1;
	disks[1] = intersect_cy_disk(ray, data, util, objid);
	tmp = find_min_value(disks[0], disks[1]);
	return (tmp);
}
