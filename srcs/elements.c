#include	"../header/structs.h"
#include	"../header/minirt.h"

void check_colors(char *rgb, t_color *location)
{
	char	**colors;
	colors = ft_split(rgb, ',');
	if(colors[0] && ft_atoi(colors[0]) <= 255 && ft_atoi(colors[0]) >= 0)
		location->r = ft_atoi(colors[0]);
	else
		location->r = -1;
	if(colors[1] && ft_atoi(colors[1]) <= 255 && ft_atoi(colors[1]) >= 0)
		location->b = ft_atoi(colors[1]);
	else
		location->b = -1;
	if(colors[2] && ft_atoi(colors[2]) <= 255 && ft_atoi(colors[2]) >= 0)
		location->g = ft_atoi(colors[2]);
	else
		location->g = -1;
	freeing_dpointer(colors);
}

int	init_A(t_data *data, char **splitted)
{
	t_amb_light	*amb;

	amb = data->elements->amb_light;
	if (splitted[1])
	{
		amb->lratio = char_to_double(splitted[1]);
		if (amb->lratio > 1 || amb->lratio < 0)
		{
			printf("ERROR\nWrong light ratio.");
			return (0);
		}
	}
	if (splitted[2])
	{
		check_colors(splitted[2], &amb->color);
		if (amb->color.r == -1 || amb->color.b == -1 || amb->color.g == -1)
		{
			printf("ERROR\nWrong ambient light color input.");
			return (0);
		}
		printf("Succcesfull Ambient light creation\n");
	}
	return (1);
}

// int	init_C(t_data *data, char **splitted)
// {
// 	t_cam	*cam;

// 	cam = data->elements->camera;
// 	if (splitted[1])
// 	{
// 		amb->lratio = char_to_double(splitted[1]);
// 		if (amb->lratio > 1 || amb->lratio < 0)
// 		{
// 			printf("ERROR\nWrong light ratio.");
// 			return (0);
// 		}
// 	}
// 	if (splitted[2])
// 	{
// 		check_colors(splitted[2], &amb->color);
// 		if (amb->color.r == -1 || amb->color.b == -1 || amb->color.g == -1)
// 		{
// 			printf("ERROR\nWrong ambient light color input.");
// 			return (0);
// 		}
// 		printf("Succcesfull Ambient light creation\n");
// 	}
// 	return (1);
// }