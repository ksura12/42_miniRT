#include	"../header/minirt.h"
#include	"../header/structs.h"

/**
 * @brief calculates from the given ray, object and data struct the incoming
 * and outgoing rays and angles between and fills the data struct "shadow"
 * with it to ahnd it to the functions for diffuse and specular light parts
 * 
 * @param data holds all data to elements and lights of the scene
 * @param ray is the incoming ray from the light source to the object
 * @param objid id to specify the obejct hitted by the ray
 * @param shadow data struct for rays and directions
 */
void	make_shadow_sp(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	shadow->intersection = get_point_of_intersection(ray->tmax, *ray);
	// printf("intersection x: %f\n", shadow->intersection.x);
	// printf("intersection y: %f\n", shadow->intersection.y);
	// printf("intersection z: %f\n", shadow->intersection.z);
	data->elements->objects[*objid]->surface_normal(data, ray, objid, shadow);
	// printf("light->v_pos. x: %f\n", data->elements->light->v_pos.x);
	// printf("light->v_pos. y: %f\n", data->elements->light->v_pos.y);
	// printf("light->v_pos. z: %f\n", data->elements->light->v_pos.z);
	shadow->to_light = vector_dev(data->elements->light->v_pos, \
		shadow->intersection);
	// printf("before cto_light x: %f\n", shadow->to_light.x);
	// printf("before cto_light y: %f\n", shadow->to_light.y);
	// printf("before cto_light z: %f\n", shadow->to_light.z);	
	shadow->to_light = normalise(shadow->to_light);

	shadow->cos_theta = dot_prod(shadow->i_normal, shadow->to_light);
	// printf("costheta: %f\n", shadow->cos_theta);
	// printf("cto_light x: %f\n", shadow->to_light.x);
	// printf("cto_light y: %f\n", shadow->to_light.y);
	// printf("cto_light z: %f\n", shadow->to_light.z);
	// printf("i_normal x: %f\n", shadow->i_normal.x);
	// printf("i_normal y: %f\n", shadow->i_normal.y);
	// printf("i_normal z: %f\n", shadow->i_normal.z);
	if (shadow->cos_theta < 0.0f)
		shadow->cos_theta = 0.0f;
	// if (shadow->cos_theta < 0.0f)
	// 	shadow->cos_theta = -shadow->cos_theta;
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

/**
 * @brief calculates from the given ray, object and data struct the incoming
 * and outgoing rays and angles between and fills the data struct "shadow"
 * with it to ahnd it to the functions for diffuse and specular light parts
 * 
 * @param data holds all data to elements and lights of the scene
 * @param ray is the incoming ray from the light source to the object
 * @param objid id to specify the obejct hitted by the ray
 * @param shadow data struct for rays and directions
 */
void	make_shadow_pl(t_data *data, t_ray *ray, int *objid, t_shadow *shadow)
{
	shadow->intersection = get_point_of_intersection(ray->tmax, *ray);
	// printf("intersection x: %f\n", shadow->intersection.x);
	// printf("intersection y: %f\n", shadow->intersection.y);
	// printf("intersection z: %f\n", shadow->intersection.z);
	shadow->i_normal = data->elements->objects[*objid]->v_orient;
	// data->elements->objects[*objid]->surface_normal(data, ray, objid, shadow);
	// printf("light->v_pos. x: %f\n", data->elements->light->v_pos.x);
	// printf("light->v_pos. y: %f\n", data->elements->light->v_pos.y);
	// printf("light->v_pos. z: %f\n", data->elements->light->v_pos.z);
	shadow->to_light = vector_dev(data->elements->light->v_pos, \
		shadow->intersection);
	// printf("before cto_light x: %f\n", shadow->to_light.x);
	// printf("before cto_light y: %f\n", shadow->to_light.y);
	// printf("before cto_light z: %f\n", shadow->to_light.z);	
	shadow->to_light = normalise(shadow->to_light);

	shadow->cos_theta = dot_prod(shadow->i_normal, shadow->to_light);
	// printf("costheta: %f\n", shadow->cos_theta);
	// printf("cto_light x: %f\n", shadow->to_light.x);
	// printf("cto_light y: %f\n", shadow->to_light.y);
	// printf("cto_light z: %f\n", shadow->to_light.z);
	// printf("i_normal x: %f\n", shadow->i_normal.x);
	// printf("i_normal y: %f\n", shadow->i_normal.y);
	// printf("i_normal z: %f\n", shadow->i_normal.z);
	// if (shadow->cos_theta < 0.0f)
	// 	shadow->cos_theta = 0.0f;
	if (shadow->cos_theta < 0.0f)
		shadow->cos_theta = -shadow->cos_theta;
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

/**
 * @brief adds up all light parts of the Phong shading model 
 * (ambient, diffuse, specular)
 * when parameter light == 1, then the object surface part is in the shadow
 * if light == 0, then object part is fully lightend up
 * 
 * @param data holds all data to elements and lights of the scene
 * @param ray is the incoming ray from the light source to the object
 * @param objid id to specify the obejct hitted by the ray
 * @param light flag for indicating if object is in the shadow(==1) or not (==0)
 * @return int hexadecimal color for coloring the pixel
 */
int	light_object(t_data *data, t_ray *ray, int *objid, int light)
{
	t_shadow	shadow;
	t_color		amb_part;
	t_color		diffu_part;
	t_color		spec_part;
	t_color		result;

	data->elements->objects[*objid]->make_shadow(data, ray, objid, &shadow);
	amb_part = amb_color(data, objid);
	// printf("amb r: %d\n", amb_part.r);
	// printf("amb g: %d\n", amb_part.g);
	// printf("amb b: %d\n", amb_part.b);
	if (light == 1)
		return (color_trgb(amb_part, 1));
	diffu_part = color_ratio(data->elements->objects[*objid]->color, \
		(shadow.cos_theta * data->elements->light->lratio \
		/ vector_len(vector_dev(data->elements->light->v_pos, \
		shadow.intersection))));
		// diffu_part = color_ratio(data->elements->objects[*objid]->color, \
		// (shadow.cos_theta * data->elements->light->lratio));
	// printf("costheta: %f\n", shadow.cos_theta);
	// printf("vector len: %f\n", vector_len(vector_dev(data->elements->light->v_pos, shadow.intersection)));
	// printf("diffu r: %d\n", diffu_part.r);
	// printf("diffu g: %d\n", diffu_part.g);
	// printf("diffu b: %d\n", diffu_part.b);
	spec_part = specular_color(data, &shadow);
	result = color_add(amb_part, diffu_part);
	result = color_limits(color_add(spec_part, result));
	return (color_trgb(result, 1));
}

/**
 * @brief calculates the ambient light part for shading
 * ambient_part = object color * amb_light color
 * 
 * @param data holds all data to elements and lights of the scene
 * @param objid id to specify the obejct hitted by the ray
 * @return t_color: the color_part for ambient in a color-struct
 */
t_color	amb_color(t_data *data, int *objid)
{
	t_color	amb_part;

	amb_part = color_mult(data->elements->objects[*objid]->color, \
		data->elements->amb_light->color);
	amb_part = color_ratio(amb_part, data->elements->amb_light->lratio);
	return (amb_part);
}

/**
 * @brief calculates the specular light part of the Phong-shading model
 * 
 * @param data holds all data to elements and lights of the scene
 * @param shadow data struct for rays and directions
 * @return t_color: the color_part for specular in a color-struct
 */
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
