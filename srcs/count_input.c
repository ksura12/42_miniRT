#include	"../header/structs.h"
#include	"../header/minirt.h"

int	check_count(t_data *data)
{
	t_counter	*counter;

	counter = data->counter;
	if (counter->ambient_light_count != 1)
	{
		printf("ERROR, declare ambient light once.\n");
		printf("Amount of ambient light is %i\n", counter->ambient_light_count);
		return (0);
	}
	if (counter->light_count != 1)
	{
		printf("ERROR, declare light once.\n");
		return (0);
	}
	if (counter->camera_count != 1)
	{
		printf("ERROR, declare camera once.\n");
		return (0);
	}
	return (1);
}

int	increase_count(t_data *data, char **splitted)
{
	if (!ft_strncmp(splitted[0], "A\0", 2))
		data->counter->ambient_light_count += 1;
	else if (!ft_strncmp(splitted[0], "C\0", 2))
		data->counter->camera_count += 1;
	else if (!ft_strncmp(splitted[0], "L\0", 2))
		data->counter->light_count += 1;
	else if (!ft_strncmp(splitted[0], "sp\0", 3))
		data->counter->sphere_count += 1;
	else if (!ft_strncmp(splitted[0], "cy\0", 3))
		data->counter->cylinder_count += 1;
	else if (!ft_strncmp(splitted[0], "pl\0", 3))
		data->counter->plane_count += 1;
	else if (splitted[0][0] == '\n')
		data->counter->newline_count += 1;
	else
	{
		printf("ERROR, unidentified element.\n");
		return (0);
	}
	return (1);
}

int	assign_info(char **splitted)
{
	int	i;

	i = 0;
	if (!ft_strncmp(splitted[0], "A\0", 2))
		i = INFO_AL;
	else if (!ft_strncmp(splitted[0], "C\0", 2))
		i = INFO_C;
	else if (!ft_strncmp(splitted[0], "L\0", 2))
		i = INFO_L;
	else if (!ft_strncmp(splitted[0], "sp\0", 3))
		i = INFO_SP;
	else if (!ft_strncmp(splitted[0], "cy\0", 3))
		i = INFO_CY;
	else if (!ft_strncmp(splitted[0], "pl\0", 3))
		i = INFO_PL;
	return (i);
}

int	count_elements(char *line, t_data *data)
{
	char	**splitted;
	int		i;

	splitted = ft_split(line, ' ');
	if (!increase_count(data, splitted))
	{
		freeing_dpointer(splitted);
		return (0);
	}
	i = assign_info(splitted);
	if (!expected_words(i, splitted))
	{
		printf("ERROR\nToo much info per element.");
		freeing_dpointer(splitted);
		return (0);
	}
	freeing_dpointer(splitted);
	return (1);
}

int	counting_elements(char **argv, t_data *data)
{
	char	*line;
	int		fd;

	fd = open_file(argv);
	line = get_next_line(fd);
	while (line)
	{
		if (!count_elements(line, data))
		{
			free(line);
			close(fd);
			return (0);
		}
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!check_count(data))
		return (0);
	else
		return (1);
}
