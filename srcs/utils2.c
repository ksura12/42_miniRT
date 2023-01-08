/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:25:53 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/08 14:34:03 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

int	open_file(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR\nFile-opening failed.");
		return (0);
	}
	return (fd);
}

/**
 * @brief converts degrees to radian
 * 
 * @param deg 
 * @return double rad
 */
double	degtorad(double deg)
{
	return (deg * M_PI / 180);
}

/**
 * @brief solves quadratic function and returns
 * smalest result
 * 
 * @param a 
 * @param b 
 * @param c 
 * @return float 
 */
float	quad_solver(float a, float b, float c)
{
	float	delta;
	float	t[2];

	delta = b * b - 4 * (a * c);
	if (fabs(delta) < EPSILON)
		return (0);
	if (delta < 0)
		return (0);
	t[0] = (-b - sqrt(delta)) / (2 * a);
	t[1] = (-b + sqrt(delta)) / (2 * a);
	return (find_min_value(t[0], t[1]));
}

/**
 * @brief compares two values and returns smalest of them
 * 
 * @param a 
 * @param b 
 * @return float the value on success, -1 on failure
 */
float	find_min_value(float a, float b)
{
	if ((isless(a, b) && isgreater(a, 0)) || (a == b))
	{
		return (a);
	}
	else if ((b < a) && (b > 0))
	{
		return (b);
	}
	else
		return (-1);
}

int	isequal(float a, float b)
{
	return ((a - 0.00001 <= b) && (a + 0.00001 >= b));
}

double	fxtod(t_fixed in)
{
	return ((double)in / (1 << FT_FIXED_FRAC_BITS));
}

/**
	@brief Converts a double to a fixed point number.
	@param in Input value as double.
	@return Input value as fixed-point.
 */
t_fixed	dtofx(double in)
{
	return ((t_fixed)(roundf(in * (1 << FT_FIXED_FRAC_BITS))));
}
