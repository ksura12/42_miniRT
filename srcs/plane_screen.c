#include	"../header/minirt.h"

int	ray_creation_plane_screen(int px, int py, t_data *data)
{
	double	scale;
	double	x;
	double	y;

	scale = tan(degtorad(data->elements->camera->fov_h * 0.5));

	x = (2 * (x + 0.5) / (float)WIDTH -1) * ASPECT_RATIO * scale;
	y = (1- 2 * (y + 0.5) / (float)HEIGHT) * scale;
	
}	