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
		if (!char_to_double(splitted[1], &amb->lratio) || amb->lratio > 1 || amb->lratio < 0)
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

// int	init_L(t_data *data, char **splitted)
// {
// 	t_light	*light;

// 	light = data->elements->light;

// 	if (splitted[1])
// 	{
// 		light->v_pos = init_vector(splitted[1]);
// 		if (light->v_pos.x == -2 || light->v_pos.y == -2 || light->v_pos.z == -2)
// 		{
// 			printf("ERROR\nWrong Camera-Viewpoint declaration.");
// 			return(0);
// 		}
// 	}
// 	if (splitted[2])
// 	{
// 		amb->lratio = char_to_double(splitted[1]);
// 		if (amb->lratio > 1 || amb->lratio < 0)
// 		{
// 			printf("ERROR\nWrong light ratio.");
// 			return (0);
// 		}
// 	}
// 	if (splitted[3])
// 	{
// 		check_colors(splitted[2], &amb->color);
// 		if (amb->color.r == -1 || amb->color.b == -1 || amb->color.g == -1)
// 		{
// 			printf("ERROR\nWrong light color input.");
// 			return (0);
// 		}
// 		printf("Succcesfull light creation\n");
// 	}
// 	return (1);
// }
/**
 * @brief check if the given char* poiunt to an all digit string 
 * with a leading + or -
 * 
 * @param value pointer to the string to test
 * @return int 0 for testing false, 1 if everything are digits
 */
int	isaldigit(char **value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (value[0][0] == '-' || value[0][0] == '+' )
		i++;
	while (value[j])
	{
		if (j != 0)
			i = 0;
		while (value[j][i])
		{
			if(!ft_isdigit(value[j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	char_to_double(char *value, double *dst)
{
	double	result;
	char	**splitted;

	splitted = ft_split(value, '.');
	//word count test
	if (!isaldigit(splitted))
		return (0);
	result = 1 * ft_atoi(splitted[0]) + 0.1 * ft_atoi(splitted[1]);
	freeing_dpointer(splitted);
	*dst = result;
	return (1);
}

t_vec	init_vector(char *xyz)
{
	t_vec	vector;
	int		i;
	char	**coordinates;

	vector.f = 0;
	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	coordinates = ft_split(xyz, ',');
	i = 0;
	// if (expected_words())
	while(coordinates[i])
		i++;
	if (i != 2)
	{
		freeing_dpointer(coordinates);
		return(vector);
	}
	vector.f = 1;
	if(!char_to_double(coordinates[0], &vector.x)
	|| !char_to_double(coordinates[1], &vector.y)
	|| !char_to_double(coordinates[2], &vector.z))
		vector.f = 0;
	freeing_dpointer(coordinates);
	return (vector);
}

int	check_boundries_vector(t_vec *vector, int min, int max)
{
	if (vector->x < min || vector->x > max)
		return(0);
	if (vector->y < min || vector->y > max)
		return(0);
	if (vector->z < min || vector->z > max)
		return(0);
	return(1);
}

int	init_C(t_data *data, char **splitted)
{
	t_cam	*cam;
	int i;

	i = 0;

	cam = data->elements->camera;
	if (splitted[1])
	{
		cam->v_pos = init_vector(splitted[1]);
		if (cam->v_pos.f == 0)
		{
			printf("ERROR\nWrong Camera-Viewpoint declaration.");
			return(0);
		}
	}
	if (splitted[2])
	{
		cam->v_orient = init_vector(splitted[2]);
		if(!check_boundries_vector(&cam->v_orient, -1, 1))
		{
			printf("ERROR\nWrong Camera-Orientation Vector declaration.");
			return(0);
		}
	}
	if (splitted[3])
	{
		while(splitted[3][i] != '\n')
		{
			if(ft_isdigit(splitted[3][i]))
				i++;
			else
			{
				printf("ERROR\nWrong Camera-Orientation Vector declaration.");
				return(0);
			}
		}
		cam->fov = ft_atoi(splitted[3]);
		if(cam->fov < 0 || cam->fov > 180)
		{
			printf("ERROR\nWrong Camera-Orientation Vector declaration.");
			return(0);
		}
		printf("Succcesfull Camera creation\n");
		printf("x-coordinate:%f\n", cam->v_pos.x);
		printf("y-coordinate:%f\n", cam->v_pos.y);
		printf("z-coordinate:%f\n", cam->v_pos.z);
	}
	return (1);
}
