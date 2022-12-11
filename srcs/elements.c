#include	"../header/structs.h"
#include	"../header/minirt.h"

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
	if (!init_camera_fov(cam, splitted))
		return (0);
	printf("Succcesfull Camera creation\n");
	return (1);
}
