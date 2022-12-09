#include	"../header/structs.h"
#include	"../header/minirt.h"

void init_counter(t_data *data)
{
	t_counter *counter;

	data->counter = malloc(sizeof(t_counter));
	counter = data->counter;
	counter->ambient_light_count = 0;
	counter->light_count = 0;
	counter->camera_count = 0;
	counter->sphere_count = 0;
	counter->cylinder_count = 0;
	counter->plane_count = 0;
	counter->newline_count = 0;
}

void init_elements(t_data *data)
{
	int obj_cont;

	obj_cont = data->counter->cylinder_count + data->counter->plane_count 
	+ data->counter->sphere_count;
	data->elements = malloc(sizeof(t_elements));
	data->elements->objects = malloc(sizeof(t_elements) * obj_cont);
}
