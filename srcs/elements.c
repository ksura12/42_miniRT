#include	"../header/structs.h"
#include	"../header/minirt.h"

int	check_colors(char *rgb, t_color *location)
{
	char	**colors;

	colors = ft_split(rgb, ',');
	if (!expected_words(3, colors))
		return (0);
	if (ft_atoi(colors[0]) <= 255 && ft_atoi(colors[0]) >= 0)
		location->r = ft_atoi(colors[0]);
	else
		return (0);
	if (ft_atoi(colors[1]) <= 255 && ft_atoi(colors[1]) >= 0)
		location->b = ft_atoi(colors[1]);
	else
		return (0);
	if (ft_atoi(colors[2]) <= 255 && ft_atoi(colors[2]) >= 0)
		location->g = ft_atoi(colors[2]);
	else
		return (0);
	freeing_dpointer(colors);
	return (1);
}

/**
 * @brief initialises ambient lights
 * 
 * @param data main data structure
 * @param splitted input parameters for amb_light from .rt file
 * @return int 0 for unsuccessfull, 1 for successfull creation
 */
int	init_a(t_data *data, char **splitted)
{
	t_amb_light	*amb;

	amb = data->elements->amb_light;
	if (splitted[1])
	{
		if (!char_to_double(splitted[1], &amb->lratio)
			|| amb->lratio > 1 || amb->lratio < 0)
		{
			printf("ERROR\nWrong light ratio.");
			return (0);
		}
	}
	if (splitted[2])
	{
		if (!check_colors(splitted[2], &amb->color))
		{
			printf("ERROR\nWrong ambient light color input.");
			return (0);
		}
		printf("Succcesfull Ambient light creation\n");
	}
	return (1);
}

/**
 * @brief initialises the light in the data structure
 * 
 * @param data main data strcuture
 * @param splitted input parameter for the light from .rt file
 * @return int 0 for fail, 1 for success in creation
 */
int	init_l(t_data *data, char **splitted)
{
	t_light	*light;

	light = data->elements->light;
	if (!expected_words(4, splitted))
	{
		printf("ERROR\nWrong Light declaration.");
		return (0);
	}
	light->v_pos = init_vector(splitted[1]);
	if (light->v_pos.f == 0
		|| !char_to_double(splitted[2], &light->lratio)
		|| light->lratio > 1 || light->lratio < 0
		|| !check_colors(splitted[3], &light->color))
	{
		printf("ERROR\nWrong light declaration.");
		return (0);
	}
	printf("Succcesfull light creation\n");
	return (1);
}

/**
 * @brief initialises the sphere in the data structure
 * 
 * @param data main data strcuture
 * @param splitted input parameter for the sphere from .rt file
 * @return int 0 for fail, 1 for success in creation
 */
int	init_s(t_data *data, char **splitted)
{
	t_obj	*obj;

	obj = data->elements->objects[data->counter->create_count];
	obj->id = 's';
	obj->v_pos = init_vector(splitted[1]);
	if (obj->v_pos.f == 0 || !char_to_double(splitted[2], &obj->dia)
		|| !check_colors(splitted[3], &obj->color))
	{
		printf("ERROR\nWrong sphere declaration.");
		return (0);
	}
	printf("Succcesfull sphere creation\n");
	printf("sphere diameter:%f\n", obj->dia);
	data->counter->create_count += 1;
	return (1);
}

/**
 * @brief initialises the cylinder in the data structure
 * 
 * @param data main data strcuture
 * @param splitted input parameter for the cylinder from .rt file
 * @return int 0 for fail, 1 for success in creation
 */
int	init_cylinder(t_data *data, char **splitted)
{
	t_obj	*obj;

	obj = data->elements->objects[data->counter->create_count];
	obj->id = 'c';
	obj->v_pos = init_vector(splitted[1]);
	obj->v_orient = init_vector(splitted[2]);
	if (obj->v_pos.f == 0 || !check_boundries_vector(&obj->v_orient, -1, 1)
		|| obj->v_orient.f == 0
		|| !char_to_double(splitted[3], &obj->dia)
		|| !char_to_double(splitted[4], &obj->height)
		|| !check_colors(splitted[5], &obj->color))
	{
		printf("ERROR\nWrong cylinder declaration.");
		return (0);
	}
	printf("Succcesfull cylinder creation\n");
	data->counter->create_count += 1;
	return (1);
}

/**
 * @brief initialises the plane in the data structure
 * 
 * @param data main data strcuture
 * @param splitted input parameter for the plane from .rt file
 * @return int 0 for fail, 1 for success in creation
 */
int	init_plane(t_data *data, char **splitted)
{
	t_obj	*obj;

	obj = data->elements->objects[data->counter->create_count];
	obj->id = 'p';
	obj->v_pos = init_vector(splitted[1]);
	obj->v_orient = init_vector(splitted[2]);
	if (obj->v_pos.f == 0 || !check_boundries_vector(&obj->v_orient, -1, 1)
		|| obj->v_orient.f == 0
		|| !check_colors(splitted[3], &obj->color))
	{
		printf("ERROR\nWrong plane declaration.");
		return (0);
	}
	printf("Succcesfull plane creation\n");
	data->counter->create_count += 1;
	return (1);
}

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
			if (!ft_isdigit(value[j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

/**
 * @brief casts a char * to a double value, checks for wrong input
 * 
 * @param value original char *
 * @param dst pointer to the double value destination
 * @return int 0 for unsuccessfull casting, 1 for successfull
 * creation of double value
 */
int	char_to_double(char *value, double *dst)
{
	double	result;
	char	**splitted;
	int		i;

	splitted = ft_split(value, '.');
	if (expected_words(1, splitted) && isaldigit(splitted))
	{
		result = ft_atoi(splitted[0]);
		freeing_dpointer(splitted);
		*dst = result;
		return (1);
	}
	else if (expected_words(2, splitted) && isaldigit(splitted))
	{
		i = 0;
		while (splitted[1][i])
		{
			i++;
		}
		result = 1 * ft_atoi(splitted[0]) + pow(0.1, i) * ft_atoi(splitted[1]);
		freeing_dpointer(splitted);
		*dst = result;
		return (1);
	}
	else
	{
		freeing_dpointer(splitted);
		return (0);
	}
}

/**
 * @brief initialises vector and fills its double parameters xyz
 * from a char pointer
 * 
 * @param xyz char pointer which holds xyz
 * @return t_vec vector structure including a flag f(1 for valid
 * vector values, 0 for wrong vector values)
 */
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
	if (!expected_words(3, coordinates))
	{
		freeing_dpointer(coordinates);
		return (vector);
	}
	vector.f = 1;
	if (!char_to_double(coordinates[0], &vector.x)
		|| !char_to_double(coordinates[1], &vector.y)
		|| !char_to_double(coordinates[2], &vector.z))
		vector.f = 0;
	freeing_dpointer(coordinates);
	return (vector);
}

/**
 * @brief check if a the parameters of a vector are in mandatory area
 * 
 * @param vector input vector structur which holds xyz
 * @param min minimum coordiante value
 * @param max max coordiante value
 * @return int 0 if outside of area, 1 if vector-parameter area is inside area
 */
int	check_boundries_vector(t_vec *vector, int min, int max)
{
	if (vector->x < min || vector->x > max)
		return (0);
	if (vector->y < min || vector->y > max)
		return (0);
	if (vector->z < min || vector->z > max)
		return (0);
	return (1);
}

/**
 * @brief initialises the field-of-view parameter of cameras
 * 
 * @param cam camera structure
 * @param splitted splitted camera input parameters
 * @return int 0 for wrong input, 1 for valid input
 */
int	init_camera_fov(t_cam *cam, char **splitted)
{
	int	i;

	i = 0;
	while (splitted[3][i] != '\n')
	{
		if (ft_isdigit(splitted[3][i]))
			i++;
		else
		{
			printf("ERROR\nWrong Camera-Orientation Vector declaration.");
			return (0);
		}
	}
	cam->fov = ft_atoi(splitted[3]);
	if (cam->fov < 0 || cam->fov > 180)
	{
		printf("ERROR\nWrong Camera field-of-view declaration.");
		return (0);
	}
	return (1);
}

/**
 * @brief initialises camera objects
 * 
 * @param data structure which holds all elements
 * @param splitted array of input parameters from .rt file for the camera
 * @return int 0 for wrong input, 1 for successfull camera creation
 */
int	init_camera(t_data *data, char **splitted)
{
	t_cam	*cam;

	cam = data->elements->camera;
	if (!expected_words(4, splitted))
	{
		printf("ERROR\nWrong Camera declaration.");
		return (0);
	}
	cam->v_pos = init_vector(splitted[1]);
	if (cam->v_pos.f == 0)
	{
		printf("ERROR\nWrong Camera-Viewpoint declaration.");
		return (0);
	}
	cam->v_orient = init_vector(splitted[2]);
	if (!check_boundries_vector(&cam->v_orient, -1, 1))
	{
		printf("ERROR\nWrong Camera-Orientation Vector declaration.");
		return (0);
	}
	if (!init_Camera_fov(cam, splitted))
		return (0);
	printf("Succcesfull Camera creation\n");
	return (1);
}
