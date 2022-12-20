#include	"../header/minirt.h"

int	diffuse_color(t_data *data, t_ray *ray, int *objid)
{
	t_vec	intersection;
	t_vec	i_normal;
	t_vec	light;
	double	costheta;
	int		color_pix;


	intersection = get_point_of_intersection(ray->tmax, *ray);
	i_normal = vector_dev(intersection, data->elements->objects[*objid]->v_pos);
	i_normal = normalise(i_normal);
	light = vector_dev(data->elements->light->v_pos, intersection);
	light = normalise(light);
	costheta = dot_prod(i_normal, light);
	if(costheta < 0.0f)
		costheta = 0.0f;
	color_pix = color_trgb(data->elements->objects[*objid]->color, costheta);
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