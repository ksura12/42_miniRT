#include	"../header/structs.h"
#include	"../header/minirt.h"

void init_counter(t_data *data)
{
	t_counter *counter;

	counter = data->counter;
	counter->ambient_light_count = 0;
	counter->light_count = 0;
	counter->camera_count = 0;
	counter->sphere_count = 0;
	counter->cylinder_count = 0;
	counter->plane_count = 0;
	counter->newline_count = 0;
}

int	init_elements(char **argv, t_data *data)
{
	char	*line;
	int		fd;
	char	**splitted;

	fd = open_file(argv);
	line = get_next_line(fd);
	splitted = NULL;
	while (line)
	{
		if (!parse_line(line, data, splitted))
		{
			free(line);
			close(fd);
			if(splitted)
				freeing_dpointer(splitted);
			return (0);//TODO- Error message for parsing
		}
		free (line);
		if(splitted)
			freeing_dpointer(splitted);
		line = get_next_line(fd);
	}
	close(fd);
	if(splitted)
		freeing_dpointer(splitted);
	return (1);
}
