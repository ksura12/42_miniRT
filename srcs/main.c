#include	"../header/structs.h"
#include	"../header/minirt.h"

int	parse_line(char *line, t_data *data, char **splitted)
{
	int stop;

	stop = 0;
	splitted = ft_split(line, ' ');
	if (!ft_strncmp(splitted[0], "A\0", 2) && !stop)
	{
		if(!init_A(data, splitted))
			stop = 1;
	}
	else if (!ft_strncmp(splitted[0], "C\0", 2))
	{
		if(!init_Camera(data, splitted))
			return(0);
	}
	else if (!ft_strncmp(splitted[0], "L\0", 2))
	{
		if(!init_L(data, splitted))
			return(0);
	}
	else if (!ft_strncmp(splitted[0], "sp\0", 3))
	{
		if(!init_s(data, splitted))
			return(0);
	}
	else if (!ft_strncmp(splitted[0], "cy\0", 3))
	{
		if(!init_cylinder(data, splitted))
			return(0);
	}
	// || !ft_strncmp(splitted[0], "cy\0", 3)
	// || !ft_strncmp(splitted[0], "pl\0", 3))
	
	// else if (!ft_strncmp(splitted[0], "cy\0", 3))
	// else if (!ft_strncmp(splitted[0], "pl\0", 3))
	// else if (splitted[0][0] == '\n')
	// else
	// {
	// 	printf("ERROR, unidentified element.\n");
	// 	freeing_dpointer(splitted);
	// 	return (0);
	// }
	freeing_dpointer(splitted);
	if (stop)
		return (0);
	return (1);
}

int	open_file(char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0); //TODO- Error messaga for file opening
	return (fd);
}

/*
void	mlx_handle(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bit_per_pix, &data->line_len, &data->endian);
	controls(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_loop(data->mlx);
}
*/

void	free_allocation(t_data *data)
{
	free(data->elements->light);
	free(data->elements->camera);
	free(data->elements->amb_light);
	free(data->elements);
	free(data->counter);
	free(data);
}

int	struct_allocation(t_data *data)
{
	data->counter = malloc(sizeof(t_counter));
	if (!data->counter)
		return (0);
	data->elements = malloc(sizeof(t_elements));
	if (!data->elements)
		return (0);
	data->elements->amb_light = malloc(sizeof(t_amb_light));
	if (!data->elements->amb_light)
		return (0);
	data->elements->light = malloc(sizeof(t_light));
	if (!data->elements->light)
		return (0);
	data->elements->camera = malloc(sizeof(t_cam));
	if (!data->elements->camera)
		return (0);
	return (1);
}

int	check_arguments(int argc, char **argv)
{
	int 	len;

	if (argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 3], ".rt", 3) != 0)
		return (0);
	return (1);
}

int	check_counter(t_data *data, char **argv)
{
	init_counter(data);
	if (!counting_elements(argv, data))
		return (0);
	return (1);
}

void	object_allocation(t_data *data)
{
	t_counter	*counter;
	int			obj_cont;
	int			i;

	counter = data->counter;
	obj_cont = counter->cylinder_count + counter->plane_count
	+ counter->sphere_count;
	i = 0;
	data->elements->objects = malloc(sizeof(t_obj *) * obj_cont);
	while (i < obj_cont)
	{
		data->elements->objects[i] = malloc(sizeof(t_obj));
		i++;
	}
}

void	parsing(int argc, char **argv, t_data *data)
{
	if (!check_arguments(argc, argv))
	{
		printf("Check your input.\n");
		exit(0);
	}	
	if (!struct_allocation(data))
	{
		printf("Allocation error.\n");
		exit(0);
	}	
	if (!check_counter(data, argv))
	{
		free_allocation(data);
		exit (0);
	}
	object_allocation(data);
	init_elements(argv, data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	//mlx_handle(data);
	parsing(argc, argv, data);
	free_allocation(data);
	return (0);
}
