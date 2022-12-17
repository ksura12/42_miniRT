#include	"../header/structs.h"
#include	"../header/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bit_per_pix / 8));
	*(unsigned int*)dst = color;
}
/*
int		color_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 )
}*/

void	render(t_data *data)
{
	int pixel_x;
	int pixel_y;
	t_ray	*ray;
	double	scale;

	// ray = NULL;
	ray = malloc (sizeof(t_ray));
	scale = tan(degtorad(data->elements->camera->fov_h * 0.5));
	pixel_y = 0;
	while (pixel_y < HEIGHT)
	{
		pixel_x = 0;
		while (pixel_x < WIDTH)
		{
			*ray = ray_creation_plane_screen(pixel_x, pixel_y, data, scale);
			intersections(data, ray, pixel_x, pixel_y);
			pixel_x++;
		}
		pixel_y++;
	}
	free(ray);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

void	intersections(t_data *data, t_ray *ray, int pixel_x, int pixel_y)
{
	int	i;
	int	color;
	double	objectnumber;

	i = 0;
	objectnumber = -1;
	color = -1;
	while(i < data->counter->create_count)
	{
		if (data->elements->objects[i]->intersection_fkt(ray, data) == 1)
		{
			objectnumber = i;
			
			
			
			
			
			
			
			
			
			
			
			
			if (shadow_rays(ray, data))
				my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00066000);
			else
				my_mlx_pixel_put(data, pixel_x, pixel_y, JUNGLE);
		}
		// else
		// {
		// 	my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00000000);
		// }
		i++;
	}
}