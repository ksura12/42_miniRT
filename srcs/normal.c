#include	"../header/minirt.h"

void	surface_normal_sp(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	(void) ray;
	shadow->i_normal = vector_dev(shadow->intersection, \
		data->elements->objects[*objid]->v_pos);
	shadow->i_normal = normalise(shadow->i_normal);
}

void	surface_normal_pl(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	(void) ray;
	shadow->i_normal = vector_dev(shadow->intersection, \
		data->elements->objects[*objid]->v_pos);
	shadow->i_normal = normalise(shadow->i_normal);
}

void	surface_normal_cy(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	(void) ray;
	(void) data;
	(void) objid;
	(void) shadow;
}
