#include	"../header/structs.h"
#include	"../header/minirt.h"

int	parse_line(char *line, t_data *data)
{
	char	**splitted;

	splitted = ft_split(line, ' ');
	if (!ft_strncmp(splitted[0], "A\0", 2))
		init_A(data, splitted);
/*	else if (!ft_strncmp(splitted[0], "C\0", 2))
		init_C(splitted);
	else if (!ft_strncmp(splitted[0], "L\0", 2))
		init_L(splitted);
	else if (!ft_strncmp(splitted[0], "sp\0", 3))
	else if (!ft_strncmp(splitted[0], "cy\0", 3))
	else if (!ft_strncmp(splitted[0], "pl\0", 3))
	else if (splitted[0][0] == '\n')
	else
	{
		printf("ERROR, unidentified element.\n");
		freeing_dpointer(splitted);
		return (0);
	}*/
	freeing_dpointer(splitted);
	return (1);
}
double	atodouble(char *value)
{
	double	result;
	char	**splitted;

	splitted = ft_split(value, '.');
	result = 1 * ft_atoi(splitted[0]) + 0.1 * ft_atoi(splitted[1]);
	return (result);

}

int	init_A(t_data *data, char **splitted)
{
	// (void)splitted;
	t_amb_light	*amb;

	amb = data->elements->amb_light;
	if (splitted[1])
	{
		amb->lratio = atodouble(splitted[1]);
		if (amb->lratio > 1 || amb->lratio < 0)
		{printf("here:%f\n", amb->lratio);
			return (0);}
	}
	printf("ratio:%f\n", amb->lratio);
	return (1);
	// amb->color->r = ;
	// amb->color->g = ;
	// amb->color->b = ;

/*
	identifier: A
∗ ambient lighting ratio in range [0.0,1.0]: 0.2
∗ R,G,B colors in range [0-255]: 255, 255, 255
*/
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

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
//	data.img = 
//	data = NULL;
	init_counter(data);
	init_elements(argv, data);
	return (load_input(argc, argv, data));

	// data = load_input(argc, argv);
	// data->win_ptr =mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");

}
