#include	"../header/minirt.h"

	// printf("angel per pixel h: %f\n", data->elements->camera->angle_horz);
	// printf("angel per pixel v: %f\n", data->elements->camera->angle_vert);
	// printf("original x: %i\n", px);
	// printf("new x: %f\n", coord.x);
	// printf("original y: %i\n", py);
	// printf("new y: %f\n", coord.y);
	// printf("angel of rotation h: %f\n",
	// (coord.x * data->elements->camera->angle_horz));
		//if - rotate for pixel row around z and for colum araound y
		//if - rotate for pixel row around x and for colum araound z
		//else - rotate for pixel row around x and for colum araound y
int	ray_create(t_data *data, t_ray *ray, int px, int py)
{
	t_coord	coord;
	t_vec	cam;
	t_vec	dir;

	cam = data->elements->camera->v_orient;
	coord = conversion(px, py);
	ray->tmax = RAY_T_MAX;
	ray->v_pos = data->elements->camera->v_pos;
	if (cam.y == 0 && cam.z == 0)
	{
		dir = vector_rot_y(cam, coord.x * data->elements->camera->angle_horz);
		dir = vector_rot_x(dir, coord.y * data->elements->camera->angle_vert);
	}
	if (cam.x == 0 && cam.z == 0)
	{
		dir = vector_rot_x(cam, coord.y * data->elements->camera->angle_vert);
		dir = vector_rot_z(dir, coord.x * data->elements->camera->angle_horz);
	}
	else
	{
		dir = vector_rot_x(cam, coord.y * data->elements->camera->angle_vert);
		dir = vector_rot_y(dir, coord.x * data->elements->camera->angle_horz);
	}
	ray->v_direct = dir;
	return (1);
}
