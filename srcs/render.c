#include	"../header/structs.h"
#include	"../header/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bit_per_pix / 8));
	*(unsigned int*)dst = color;
}

int		color_trgb(t_color color, double lratio)
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

void	intersections(t_data *data, t_ray *ray, int pixel_x, int pixel_y)
{
	int	i;
	int	color;
	int	objid;
	// double	facingratio;
	// double	brightness;

	// brightness = data->elements->amb_light->lratio + data->elements->light->lratio;

	// facingratio = 1;
	color = BLACK;
	i = 0;
	objid = -1;
	while(i < data->counter->create_count)
	{
		data->elements->objects[i]->intersection_fkt(ray, data, i, &objid);
		i++;
	}
	if (objid != -1)
	{
		if (shadow_rays(ray, data) == 1)
			color = BLACK;
		else
			color = diffuse_color(data, ray, &objid);
		// if (shadow_rays(ray, data) == 1)
		// 	color = color_trgb(data->elements->objects[objid]->color, data->elements->amb_light->lratio / brightness * 100);
		// else
		// 	color = color_trgb(data->elements->objects[objid]->color, 1);
	}
	my_mlx_pixel_put(data, pixel_x, pixel_y, color);
}
