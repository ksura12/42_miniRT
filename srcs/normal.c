#include	"../header/minirt.h"

void	normal_sphere(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	(void) ray;
	shadow->i_normal = vector_dev(shadow->intersection, \
		data->elements->objects[*objid]->v_pos);
	shadow->i_normal = normalise(shadow->i_normal);
}

