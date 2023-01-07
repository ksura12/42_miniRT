/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:23:38 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 09:08:03 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

/**
 * @brief make a vector with length 1
 * 
 * @param vector orininal vector
 * @return t_vec unit vector with length 1
 */
t_vec	normalise(t_vec vector)
{
	t_vec	v;

	v.x = vector.x / vector_len(vector);
	v.y = vector.y / vector_len(vector);
	v.z = vector.z / vector_len(vector);
	return (v);
}

/**
 * @brief multiplies vector with 4x4matrix
 * 
 * @param vec vector to convert
 * @param mat (double) double pointer to matrix for convertion of vector
 * @return t_vec converted vector
 */
t_vec	mult_vec_mat(t_vec vec, double **mat)
{
	t_vec	ret;

	ret.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z
		* mat[2][0] + mat[3][0];
	ret.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z
		* mat[2][1] + mat[3][1];
	ret.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z
		* mat[2][2] + mat[3][2];
	ret.f = 1;
	return (ret);
}

/**
 * @brief negates each coordinat of vector/point
 * 
 * @param vec original vector
 * @return t_vec opposite vector
 */
t_vec	make_opposite_vector(t_vec vec)
{
	t_vec	opp;

	opp.x = -vec.x;
	opp.y = -vec.y;
	opp.z = -vec.z;
	return (opp);
}

/**
 * @brief addition of two vector/point values
 * 
 * @param a first vector/point
 * @param b second vector/point
 * @return t_vec resulting vector/point
 */
t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

/**
 * @brief compares two vectors if they are the same, returns 0 if
 * they are different, 1 if they are similar
 * 
 * @param a first vector
 * @param b second vector
 * @return int: 0 for different, 1 for identical
 */
int	vec_comp(t_vec a, t_vec b)
{
	if (a.f != b.f)
		return (0);
	if (a.x != b.x)
		return (0);
	if (a.y != b.y)
		return (0);
	if (a.z != b.z)
		return (0);
	return (1);
}
