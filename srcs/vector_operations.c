/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:23:45 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 09:12:25 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

/**
 * @brief creates a vector from three values
 * 
 * @param x 
 * @param y 
 * @param z 
 * @return t_vec assembled vector struct
 */
t_vec	make_vector(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/**
 * @brief calculates dot product of two vectors
 * 
 * @param v1 first vector
 * @param v2 second vector
 * @return [double] the dot product
 */
double	dot_prod(t_vec v1, t_vec v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/**
 * @brief calculates the square of vector length
 * 
 * @param v 
 * @return [double] value of length squared
 */
double	vector_lensqr(t_vec v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

/**
 * @brief calculates the length of a vector
 * 
 * @param v 
 * @return [double] value of lenght 
 */
double	vector_len(t_vec v)
{
	return (sqrtf(vector_lensqr(v)));
}

/**
 * @brief calculates cross product of two vectors
 * 
 * @param v1 
 * @param v2 
 * @return t_vec resuling vector
 */
t_vec	cross_prod(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}
