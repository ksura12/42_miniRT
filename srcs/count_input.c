#include	"../header/structs.h"
#include	"../header/minirt.h"

int	counting_elements(char **argv, t_data *data);
int	count_elements(char *line, t_data *data);
int	check_count(t_data *data);

int	check_count(t_data *data)
{
	t_counter	*counter;

	counter = data->counter;
	if (counter->ambient_light_count != 1)
	{
		printf("ERROR, declare ambient light once.\n");
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

// int	analyze_line(void *structure, )
// {

// 	data->counter-> += 1;
// }

int	count_elements(char *line, t_data *data)
{
	char	**splitted;

	splitted = ft_split(line, ' ');
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

int	expected_words(int expected, char **words)
{
	int	i;

	i = 0;
	while(words[i] && words[i][0] != '\n')
		i++;
	if (i == expected)
		return (1);
	else
		return (0);
}
