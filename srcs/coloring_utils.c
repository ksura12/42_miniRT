/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:24:07 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 05:24:09 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minirt.h"

/**
 * @brief check if one of the trgb values is over 255 and set it to 255
 * if it is the case
 * 
 * @param color to check the trgb values
 * @return t_color: the corrected trgb color-struct
 */
t_color	color_limits(t_color color)
{
	if (color.t > 255)
		color.t = 255;
	if (color.r > 255)
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	return (color);
}

/**
 * @brief multiplies a given trgb color struct with a given light ratio(lratio)
 * factor
 * 
 * @param color color which to multiply with lratio
 * @param lratio factor tor multiply trgb color-struct with
 * @return t_color: product of trgb color-struct and lratio
 */
t_color	color_ratio(t_color color, double lratio)
{
	color.t = color.t * lratio;
	color.r = color.r * lratio;
	color.g = color.g * lratio;
	color.b = color.b * lratio;
	return (color);
}

/**
 * @brief multiplicates two trgb color-structs with oneanoter
 * 
 * @param object is the trgb-color of the object
 * @param light ist trgb-color of the hitting light
 * @return t_color: thte trgb color-struct for the resulting color
 */
t_color	color_mult(t_color object, t_color light)
{
	t_color	color;

	color.t = (object.t / 255 * light.t / 255) * 255;
	color.r = (object.r / 255 * light.r / 255) * 255;
	color.g = (object.g / 255 * light.g / 255) * 255;
	color.b = (object.b / 255 * light.b / 255) * 255;
	return (color);
}

/**
 * @brief adding two trgb-colors
 * 
 * @param a first trgb-color
 * @param b second trgb-color to add to the first
 * @return t_color 
 */
t_color	color_add(t_color a, t_color b)
{
	t_color	sum;

	sum.t = a.t + b.t;
	sum.r = a.r + b.r;
	sum.g = a.g + b.g;
	sum.b = a.b + b.b;
	return (sum);
}
