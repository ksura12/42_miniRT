#include	"../header/structs.h"
#include	"../header/minirt.h"

void init(t_data *data)
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
