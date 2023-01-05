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
	shadow->intersection.x = 0.0;
	shadow->intersection.y = 0.0;
	shadow->intersection.z = 0.0;
//	if (dot_prod(ray->v_direct, data->elements->objects[*objid]->v_orient) < 0)
		shadow->i_normal = vec_mult(data->elements->objects[*objid]->v_orient, 1);
//	else
//		shadow->i_normal = vec_mult(data->elements->objects[*objid]->v_orient, -1);
}

void	surface_normal_cy(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	(void) ray;
	(void) data;
	(void) objid;
	(void) shadow;
	// shadow->i_normal = get_point_of_intersection(ray->tmax, ray)
}
