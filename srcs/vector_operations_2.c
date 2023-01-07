/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:23:26 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 05:23:28 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

t_vec	vector_dev(t_vec u, t_vec v)
{
	t_vec	ret;

	ret.x = u.x - v.x;
	ret.y = u.y - v.y;
	ret.z = u.z - v.z;
	return (ret);
}

t_vec	vector_rot_x(t_vec v, double alpha)
{
	t_vec	rot;

	rot.x = v.x;
	rot.y = v.y * cos(degtorad(alpha)) - v.z * sin(degtorad(alpha));
	rot.z = v.y * sin(degtorad(alpha)) + v.z * cos(degtorad(alpha));
	return (rot);
}

t_vec	vector_rot_y(t_vec v, double alpha)
{
	t_vec	rot;

	rot.x = v.x * cos(degtorad(alpha)) + v.z * sin(degtorad(alpha));
	rot.y = v.y;
	rot.z = -v.x * sin(degtorad(alpha)) + v.z * cos(degtorad(alpha));
	return (rot);
}

t_vec	vector_rot_z(t_vec v, double alpha)
{
	t_vec	rot;

	rot.x = v.x * cos(degtorad(alpha)) - v.y * sin(degtorad(alpha));
	rot.y = v.x * sin(degtorad(alpha)) + v.y * cos(degtorad(alpha));
	rot.z = v.z;
	return (rot);
}
