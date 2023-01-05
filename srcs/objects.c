#include	"../header/structs.h"
#include	"../header/minirt.h"

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
	obj->intersection_fkt = &does_intersect_s;
	obj->surface_normal = &surface_normal_sp;
	obj->make_shadow = &make_shadow_sp;
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
	printf("sphere x:%f\n", obj->v_pos.x);
	printf("sphere y:%f\n", obj->v_pos.y);
	printf("sphere z:%f\n", obj->v_pos.z);
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
	obj->intersection_fkt = &does_intersect_cy;
	obj->surface_normal = &surface_normal_cy;
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
	obj->intersection_fkt = &does_intersect_p;
	obj->surface_normal = &surface_normal_pl;
	obj->make_shadow = &make_shadow_pl;
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
	char	**coordinates;

	vector.f = 0;
	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	coordinates = ft_split(xyz, ',');
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
