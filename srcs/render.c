/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:25:46 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/08 14:33:49 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/structs.h"
#include	"../header/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bit_per_pix / 8));
	*(unsigned int *)dst = color;
}

int	color_trgb(t_color color, double lratio)
{
	color.t = color.t * lratio;
	color.r = color.r * lratio;
	color.g = color.g * lratio;
	color.b = color.b * lratio;
	return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}

void	render(t_data *data)
{
	int		pixel_x;
	int		pixel_y;
	t_ray	ray;
	double	scale;

	scale = tan(degtorad(data->elements->camera->fov_h * 0.5));
	pixel_y = 0;
	while (pixel_y < HEIGHT)
	{
		pixel_x = 0;
		while (pixel_x < WIDTH)
		{
			ray = ray_creation_plane_screen(pixel_x, pixel_y, data, scale);
			intersections(data, &ray, pixel_x, pixel_y);
			pixel_x++;
		}
		pixel_y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

int	color_background(t_data *data)
{
	t_color		background;
	t_amb_light	*amb_light;

	amb_light = data->elements->amb_light;
	background.t = amb_light->color.t * amb_light->lratio;
	background.r = amb_light->color.r * amb_light->lratio;
	background.g = amb_light->color.g * amb_light->lratio;
	background.b = amb_light->color.b * amb_light->lratio;
	return (background.t << 24 | background.r << 16
		| background.g << 8 | background.b);
}

// double	facingratio;
// double	brightness;
// brightness = 
// data->elements->amb_light->lratio + data->elements->light->lratio;
// facingratio = 1;
// if (shadow_rays(ray, data) == 1)
//color = 
//color_trgb(data->elements->objects[objid]->color, 
//data->elements->amb_light->lratio / brightness * 100);
// else
// 	color = color_trgb(data->elements->objects[objid]->color, 1);
void	intersections(t_data *data, t_ray *ray, int pixel_x, int pixel_y)
{
	int	i;
	int	color;
	int	objid;

	color = color_background(data);
	i = 0;
	objid = -1;
	ray->cy_cap = 2;
	while (i < data->counter->create_count)
	{
		data->elements->objects[i]->intersection_fkt(ray, data, i, &objid);
		i++;
	}
	if (objid != -1)
	{
		if (shadow_rays(ray, data) > 0)
			color = light_object(data, ray, &objid, 1);
		else
			color = light_object(data, ray, &objid, 0);
	}
	my_mlx_pixel_put(data, pixel_x, pixel_y, color);
}
