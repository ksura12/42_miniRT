/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:18:35 by ksura@student.42  #+#    #+#             */
/*   Updated: 2022/11/29 20:21:47 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * struct for vectors consisting out of three parameters
 * @param x [double] Value for the X-Component of the vector
 * @param y [double] Value for the Y-Component of the vector
 * @param z [double] Value for the Z-Component of the vector
*/
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

#endif