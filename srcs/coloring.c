#include	"../header/minirt.h"

t_color		color_mult(t_color color, double lratio)
{
	color.t = color.t * lratio;
	color.r = color.r * lratio;
	color.g = color.g * lratio;
	color.b = color.b * lratio;
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
	// t_color	amb_part;
	t_color	diffu_part;
	t_color	spec_part;
	t_color	result;
	t_color	object_color;


	intersection = get_point_of_intersection(ray->tmax, *ray);
	i_normal = vector_dev(intersection, data->elements->objects[*objid]->v_pos);
	i_normal = normalise(i_normal);
	to_light = vector_dev(data->elements->light->v_pos, intersection);
	to_light = normalise(to_light);
	costheta = dot_prod(i_normal, to_light);
	if(costheta < 0.0f)
		costheta = 0.0f;
	// amb_part = color_mult(data->elements->amb_light->color, data->elements->amb_light->lratio)
	diffu_part = color_mult(data->elements->objects[*objid]->color, costheta);
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
	cos_angle = pow(cos_angle, 20);
	spec_part = color_mult(data->elements->light->color, cos_angle);
	result = color_add(diffu_part, spec_part);
	object_color =   color_mult(diffu_part, 1.0 - cos_angle);
	// result = diffu_part;
	result = color_add(spec_part, object_color);
	color_pix = color_trgb(result, 1);
	return (color_pix);
}

// Point lightPosition = PointMake(-100.0f, 100.0f, -100.0f);
// Color diffuseColor  = ColorMake(0.0f, 1.0f, 0.0f);
// Color specularColor = ColorMake(1.0f, 1.0f, 1.0f);
// Color pixelColor    = ColorMake(0.0f, 0.0f, 0.0f);

// //  Trace...

//             // Diffuse
//             Point intersectionPosition = PointMake(x, y, z);
//             Vector intersectionNormal = VectorMake((x - xs) / rs, (y - ys) / rs, (z - zs) / rs);
//             Vector intersectionNormalN = VectorNormalize(intersectionNormal);
//             Vector lightVector          = VectorSubtract(lightPosition, intersectionPosition);
//             VectorlightVectorN         = VectorNormalize(lightVector);
//             float      cosTheta        = VectorDotProduct(intersectionNormalN, lightVectorN);
//             if (cosTheta < 0.0f)
//             {
//                 cosTheta = 0.0f;
//             }

//             pixelColor = ColorMultScalar(diffuseColor, cosTheta);

//             // Specular
//             Vector incomVector    = VectorSubtract(intersectionPosition, lightPosition);
//             Vector incomVectorN   = VectorNormalize(incomVector);

//             float myDot = - VectorDotProduct(incomVectorN, intersectionNormalN);
//             float myLen = 2.0f * myDot;

//             Vector tempNormal     = VectorMultScalar(intersectionNormalN, myLen);
//             Vector reflectVector  = VectorAdd(tempNormal, incomVectorN);
//             Vector reflectVectorN = VectorNormalize(reflectVector);

//             float mySpec = MAX(-VectorDotProduct(reflectVectorN, incomVectorN), 0);
//             mySpec       = powf(mySpec, 5);

//             specularColor = ColorMultScalar(specularColor, mySpec);
//             pixelColor    = ColorAdd(pixelColor, specularColor);
//             pixelColor    = ColorClamp(pixelColor);

//             [self putPixelatX:i andY:j andR:pixelColor.r andG:pixelColor.g andB:pixelColor.b];



// // Fragment shader program
// precision mediump int;
// precision mediump float;

// // Light model
// uniform vec3 u_Light_position;
// uniform vec3 u_Light_color;
// uniform float u_Shininess;

// // Data coming from the vertex shader
// varying vec3 v_Vertex;
// varying vec4 v_Color;
// varying vec3 v_Normal;

// void main() {

//   vec3 to_light;
//   vec3 vertex_normal;
//   vec3 reflection;
//   vec3 to_camera;
//   float cos_angle;
//   vec3 specular_color;
//   vec3 object_color;
//   vec3 color;

//   // Calculate a vector from the fragment location to the light source
//   to_light = u_Light_position - v_Vertex;
//   to_light = normalize( to_light );

//   // The vertex's normal vector is being interpolated across the primitive
//   // which can make it un-normalized. So normalize the vertex's normal vector.
//   vertex_normal = normalize( v_Normal );

//   // Calculate the reflection vector
//   reflection = 2.0 * dot(vertex_normal,to_light) * vertex_normal - to_light;

//   // Calculate a vector from the fragment location to the camera.
//   // The camera is at the origin, so negating the vertex location gives the vector
//   to_camera = -1.0 * v_Vertex;

//   // Calculate the cosine of the angle between the reflection vector
//   // and the vector going to the camera.
//   reflection = normalize( reflection );
//   to_camera = normalize( to_camera );
//   cos_angle = dot(reflection, to_camera);
//   cos_angle = clamp(cos_angle, 0.0, 1.0);
//   cos_angle = pow(cos_angle, u_Shininess);

//   // If this fragment gets a specular reflection, use the light's color,
//   // otherwise use the objects's color
//   specular_color = u_Light_color * cos_angle;
//   object_color = vec3(v_Color) * (1.0 - cos_angle);
//   color = specular_color + object_color;

//   gl_FragColor = vec4(color, v_Color.a);
// }