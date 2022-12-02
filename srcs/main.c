
#include	"../header/structs.h"
#include	"../header/minirt.h"

int	parsing_line(char *line, t_data *data)
{
	(void) line;
	(void) data;
	return (0);
}

int	check_input(int argc, char **argv, t_data *data)
{
	int 	len;
	int		fd;
	// int 	i;
	char	*line;

	if(argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 3], ".rt", 3) != 0)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0); //TODO- Error messaga for file opening
	line = get_next_line(fd);
	while (line)
	{
		if (parsing_line(line, data))
		{
			free(line);
			close(fd);
			return (0);//TODO- Error message for parsing
		}
		free (line);
		printf("line = %s\n", line);
		line = get_next_line(fd);
	}
	//TODO -- get number of lines in file
	//use get_next line to fill array with objects
	close(fd);
	return (1);
}

int	load_input(int argc, char **argv, t_data *data)
{
	if (!check_input(argc, argv, data))
	{
		printf("check your input\n");
		exit(0);
	}
	return (1);

}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	return (load_input(argc, argv, data));
	
	// data = load_input(argc, argv);
	// data->win_ptr =mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");

}