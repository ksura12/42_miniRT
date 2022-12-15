#include	"../header/structs.h"
#include	"../header/minirt.h"

int	struct_allocation(t_data *data)
{
	data->counter = malloc(sizeof(t_counter));
	if (!data->counter)
		return (0);
	data->elements = malloc(sizeof(t_elements));
	if (!data->elements)
		return (0);
	data->elements->amb_light = malloc(sizeof(t_amb_light));
	if (!data->elements->amb_light)
		return (0);
	data->elements->light = malloc(sizeof(t_light));
	if (!data->elements->light)
		return (0);
	data->elements->camera = malloc(sizeof(t_cam));
	if (!data->elements->camera)
		return (0);
	data->elements->camera->camtoworld = malloc(sizeof(double **));
	if (!data->elements->camera->camtoworld)
		return (0);
	return (1);
}

void	object_allocation(t_data *data)
{
	t_counter	*counter;
	int			obj_cont;
	int			i;

	counter = data->counter;
	obj_cont = counter->cylinder_count + counter->plane_count
		+ counter->sphere_count;
	i = 0;
	data->elements->objects = malloc(sizeof(t_obj *) * obj_cont);
	while (i < obj_cont)
	{
		data->elements->objects[i] = malloc(sizeof(t_obj));
		i++;
	}
}
