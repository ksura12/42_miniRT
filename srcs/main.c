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
		if(!init_C(data, splitted))
			return(0);
	}
	// else if (!ft_strncmp(splitted[0], "L\0", 2))
	// 	init_L(splitted);
	// else if (!ft_strncmp(splitted[0], "sp\0", 3))
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

double	char_to_double(char *value)
{
	double	result;
	char	**splitted;

	splitted = ft_split(value, '.');
	result = -1;
	
	if (splitted[0] && splitted[1])
		result = 1 * ft_atoi(splitted[0]) + 0.1 * ft_atoi(splitted[1]);
	freeing_dpointer(splitted);
	return (result);

}

int	open_file(char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0); //TODO- Error messaga for file opening
	return (fd);
}

int	load_input(int argc, char **argv, t_data *data)
{
	int 	len;

	if (argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 3], ".rt", 3) != 0)
		return (0);
	if (!counting_elements(argv, data))
	{
		printf("check your input\n");
		exit(0);
	}
	return (1);
}

/*



void	mlx_handle(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bit_per_pix, &data->line_len, &data->endian);
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

void	check_counter(t_data *data, char **argv)
{
	init_counter(data);
	counting_elements(argv, data);
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
	check_counter(data, argv);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	parsing(argc, argv, data);
//	allocating_elements(data);
//	load_input(argc, argv, data);
//	init_elements(argv, data);
	// controls(data);
	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	// mlx_loop(data->mlx);
	return (0);

	// data = load_input(argc, argv);
	// data->win_ptr =mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");

}
