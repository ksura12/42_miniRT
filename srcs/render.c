#include	"../header/structs.h"
#include	"../header/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bit_per_pix / 8));
	*(unsigned int*)dst = color;
}

int		color_trgb(t_color color)
{

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
	int	objid;

	i = 0;
	objid = -1;
	while(i < data->counter->create_count)
	{
		data->elements->objects[i]->intersection_fkt(ray, data, i, &objid);
		i++;
	}
	if (objid != -1)
	{
		my_mlx_pixel_put(data, pixel_x, pixel_y, color_trgb(data->elements->objects[objid]->color));
	}
	// color_trgb(data->elements->objects[i]->color
	else
		my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00000000);
	
	// if ( *objid != -1)
	// {
	// 	i = 0;
	// 	while(i < data->counter->create_count)
	// 	{
	// 		if (shadow_rays(ray, data) == 1)
	// 			my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00066000); // put pixel with color of object[objid] in shadow
	// 		i++;
	// 	}
	// }
	// 	i++;
	// }	
	// 		if (shadow_rays(ray, data))
	// 			my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00066000);
	// 		else
	// 			my_mlx_pixel_put(data, pixel_x, pixel_y, JUNGLE);
	// 	}
	// 	// else
	// 	// {
	// 	// 	my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00000000);
	// 	// }
	// 	i++;
	// }
}