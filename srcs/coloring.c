#include	"../header/minirt.h"

void	make_shadow(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	shadow->intersection = get_point_of_intersection(ray->tmax, *ray);
	shadow->i_normal = vector_dev(shadow->intersection, \
		data->elements->objects[*objid]->v_pos);
	shadow->i_normal = normalise(shadow->i_normal);
	shadow->to_light = vector_dev(data->elements->light->v_pos, \
		shadow->intersection);
	shadow->to_light = normalise(shadow->to_light);
	shadow->cos_theta = dot_prod(shadow->i_normal, shadow->to_light);
	if (shadow->cos_theta < 0.0f)
		shadow->cos_theta = 0.0f;
	shadow->from_light = vector_dev(shadow->intersection, \
		data->elements->light->v_pos);
	shadow->from_light = normalise(shadow->from_light);
	shadow->reflection = vec_mult(shadow->i_normal, dot_prod(shadow->i_normal, \
		shadow->to_light) * 2);
	shadow->reflection = vector_dev(shadow->reflection, shadow->to_light);
	shadow->reflection = normalise(shadow->reflection);
	shadow->to_cam = vector_dev(data->elements->camera->v_pos, \
		shadow->intersection);
	shadow->to_cam = normalise(shadow->to_cam);
}

int	light_object(t_data *data, t_ray *ray, int *objid, int light)
{
	t_shadow	shadow;
	t_color		amb_part;
	t_color		diffu_part;
	t_color		spec_part;
	t_color		result;

	make_shadow(data, ray, objid, &shadow);
	amb_part = amb_color(data, objid);
	if (light == 1)
		return (color_trgb(amb_part, 1));
	diffu_part = color_ratio(data->elements->objects[*objid]->color, \
		(shadow.cos_theta * data->elements->light->lratio \
		/ vector_len(vector_dev(data->elements->light->v_pos, \
		shadow.intersection))));
	spec_part = specular_color(data, &shadow);
	result = color_add(amb_part, diffu_part);
	result = color_ratio(result, 1.0);
	result = color_limits(color_add(spec_part, result));
	return (color_trgb(result, 1));
}

t_color	amb_color(t_data *data, int *objid)
{
	t_color	amb_part;

	amb_part = color_mult(data->elements->objects[*objid]->color, \
		data->elements->amb_light->color);
	amb_part = color_ratio(amb_part, data->elements->amb_light->lratio);
	return (amb_part);
}

t_color	specular_color(t_data *data, t_shadow *shadow)
{
	t_color	spec_part;
	double	shininess;
	double	r;

	shininess = 10;
	shadow->cos_theta = dot_prod(shadow->reflection, shadow->to_cam);
	if (shadow->cos_theta < 0.0f)
		shadow->cos_theta = 0.0f;
	shadow->cos_theta = pow(shadow->cos_theta, shininess);
	r = vector_len(vector_dev(data->elements->light->v_pos, \
		shadow->intersection));
	spec_part = color_ratio(data->elements->light->color, \
		(shadow->cos_theta * data->elements->light->lratio / r));
	return (spec_part);
}
