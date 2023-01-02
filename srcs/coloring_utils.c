#include	"../header/minirt.h"

t_color	color_limits(t_color color)
{
	if (color.t > 255)
		color.t = 255;
	if (color.r > 255)
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	return (color);
}

t_color	color_ratio(t_color color, double lratio)
{
	color.t = color.t * lratio;
	color.r = color.r * lratio;
	color.g = color.g * lratio;
	color.b = color.b * lratio;
	return (color);
}

t_color	color_mult(t_color object, t_color light)
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
