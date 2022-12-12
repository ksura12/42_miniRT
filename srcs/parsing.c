#include	"../header/structs.h"
#include	"../header/minirt.h"

int	parse_line(char *line, t_data *data, char **splitted)
{
	int	stop;

	stop = 1;
	splitted = ft_split(line, ' ');
	if (!ft_strncmp(splitted[0], "A\0", 2) && !stop)
	{
		if (!init_a(data, splitted))
			stop = 0;
	}
	else if (!ft_strncmp(splitted[0], "C\0", 2))
	{
		if (!init_camera(data, splitted))
			stop = 0;
	}
	else if (!ft_strncmp(splitted[0], "L\0", 2))
	{
		if (!init_l(data, splitted))
			stop = 0;
	}
	else if (!ft_strncmp(splitted[0], "sp\0", 3))
	{
		if (!init_s(data, splitted))
			stop = 0;
	}
	else if (!ft_strncmp(splitted[0], "cy\0", 3))
	{
		if (!init_cylinder(data, splitted))
			stop = 0;
	}
	else if (!ft_strncmp(splitted[0], "pl\0", 3))
	{
		if (!init_plane(data, splitted))
			stop = 0;
	}
	freeing_dpointer(splitted);
	if (!stop)
		return (0);
	return (1);
}

int	check_arguments(int argc, char **argv)
{
	int	len;

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
