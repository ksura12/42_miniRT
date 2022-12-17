#include	"../header/structs.h"
#include	"../header/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bit_per_pix / 8));
	*(unsigned int*)dst = color;
}

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
			// ray_create(data, &ray, pixel_x, pixel_y);
			*ray = ray_creation_plane_screen(pixel_x, pixel_y, data, scale);
			// printf("ray.pos.x: %f\n", ray.v_pos.x);
			// printf("ray.pos.y: %f\n", ray.v_pos.y);
			// printf("ray.pos.z: %f\n", ray.v_pos.z);
			// printf("ray.direct.x: %f\n", ray.v_direct.x);
			// printf("ray.direct.y: %f\n", ray.v_direct.y);
			// printf("ray.direct.z: %f\n", ray.v_direct.z);
			if (does_intersect_s(ray, data) == 1)
			{
				// printf("render ray tmax : %f\n", ray->tmax);
				if (shadow_rays(ray, data))
					my_mlx_pixel_put(data, pixel_x, pixel_y, JUNGLE);
				else
					my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00000000);
				// printf("1 ray direction pixel %i x/y/z: %f/%f/%f\n", pixel_x, ray.v_direct.x, ray.v_direct.y, ray.v_direct.z);
			}
				
			else
			{
				my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00000000);
				// printf("0 ray direction pixel %i x/y/z: %f/%f/%f\n", pixel_x, ray.v_direct.x, ray.v_direct.y, ray.v_direct.z);
			}
			
			pixel_x++;
		}
		pixel_y++;
	}
	free(ray);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}
