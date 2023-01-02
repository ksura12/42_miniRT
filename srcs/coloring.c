#include	"../header/minirt.h"


 t_color	color_limits(t_color color)
 {
	if(color.t > 255)
		color.t = 255;
	if(color.r > 255)
		color.r = 255;
	if(color.g > 255)
		color.g = 255;
	if(color.b > 255)
		color.b = 255;
	return (color);

 }

t_color		color_ratio(t_color color, double lratio)
{
	color.t = color.t * lratio;
	color.r = color.r * lratio;
	color.g = color.g * lratio;
	color.b = color.b * lratio;
	return (color);
}

t_color		color_mult(t_color object, t_color light)
{
	t_color	color;
	color.t = (object.t / 255 * light.t / 255) * 255;
	color.r = (object.r / 255 * light.r / 255) * 255;
	color.g = (object.g / 255 * light.g / 255) * 255;
	color.b = (object.b / 255 * light.b / 255) * 255;
	return (color);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	sum;
	sum.t = a.t + b.t;
	sum.r = a.r + b.r;
	sum.g = a.g + b.g;
	sum.b = a.b + b.b;
	return (sum);

}

int	diffuse_color(t_data *data, t_ray *ray, int *objid)
{
	t_vec	intersection;
	t_vec	i_normal;
	t_vec	to_light;
	t_vec	from_light;
	t_vec	reflection;
	t_vec	to_cam;

	double	costheta;
	double	cos_angle;
	int		color_pix;
	t_color	amb_part;
	t_color	diffu_part;
	t_color	spec_part;
	t_color	result;
	t_color	object_color;

// light = ambient + diffuse + specular
// ambient = objectcolor * lightcolor *ambientlightratio

	amb_part = color_mult(data->elements->objects[*objid]->color, data->elements->amb_light->color);
	amb_part = color_ratio(amb_part, data->elements->amb_light->lratio);
	intersection = get_point_of_intersection(ray->tmax, *ray);
	i_normal = vector_dev(intersection, data->elements->objects[*objid]->v_pos);
	i_normal = normalise(i_normal);
	to_light = vector_dev(data->elements->light->v_pos, intersection);
	to_light = normalise(to_light);
	costheta = dot_prod(i_normal, to_light);
	if(costheta < 0.0f)
		costheta = 0.0f;
	// amb_part = color_mult(data->elements->amb_light->color, data->elements->amb_light->lratio)
	diffu_part = color_ratio(data->elements->objects[*objid]->color, costheta);
	from_light = vector_dev(intersection, data->elements->light->v_pos);
	from_light = normalise(from_light);
	reflection = vec_mult(i_normal, dot_prod(i_normal,to_light) * 2);
	reflection = vector_dev(reflection, to_light);
	reflection = normalise(reflection);
	to_cam = vector_dev(data->elements->camera->v_pos, intersection);
	to_cam = normalise(to_cam);
	cos_angle = dot_prod(reflection, to_cam);
	if(cos_angle < 0.0f)
		cos_angle = 0.0f;
	cos_angle = pow(cos_angle, 5);
	spec_part = color_ratio(data->elements->light->color, cos_angle);
	result = color_add(amb_part, diffu_part);
	// result = color_add(result, spec_part);
	object_color = color_ratio(result, 1.0 - cos_angle);
	// result = diffu_part;
	result = color_add(spec_part, object_color);
	// color_pix = color_trgb(result, 1);
	// (void) result;
	result = color_limits(result);
	color_pix = color_trgb(result, 1);
	return (color_pix);
}

int	amb_color(t_data *data, int *objid)
{
	int		color_pix;
	t_color	amb_part;

	amb_part = color_mult(data->elements->objects[*objid]->color, data->elements->amb_light->color);
	amb_part = color_ratio(amb_part, data->elements->amb_light->lratio);
	color_pix = color_trgb(amb_part, 1);
	return (color_pix);
}

