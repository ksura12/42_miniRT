/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:33:43 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/08 13:54:31 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/structs.h"
#include	"../header/minirt.h"

int	parsing_line(char *line, t_data *data)
{
	(void) data;
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(line, ' ');
	while (splitted[i])
	{
		printf("splitted line = %s\n", splitted[i]);
		if (splitted[i][0] == '\n')
			break ;
		i++;
	}
	if (!ft_strncmp(splitted [0], "A\0", 2))
		printf("AMBIENT LIGHT found\n");
	else if (!ft_strncmp(splitted [0], "C\0", 2))
		printf("CAMERA found\n");
	else if (!ft_strncmp(splitted [0], "L\0", 2))
		printf("LIGHT found\n");
	else if (!ft_strncmp(splitted [0], "sp\0", 3))
		printf("SPHERE found\n");
	else if (!ft_strncmp(splitted [0], "cy\0", 3))
		printf("CYLINDER found\n");
	else if (!ft_strncmp(splitted [0], "pl\0", 3))
		printf("PLANE found\n");
	else
		printf("ERROR\n");
	return (0);
}

void	ambient_light(t_data *data)
{
	t_elements 	element;
	t_amb_light amb_light;

	element = data->elements;
	amb_light = element->amb_light;
	element->ambient_light_count += 1;

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
		free (splitted);
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
