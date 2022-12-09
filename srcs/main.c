/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:33:43 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/09 15:06:15 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/structs.h"
#include	"../header/minirt.h"

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

// void	ambient_light(t_data *data, char **splitted)
// {
// 	(void)splitted;
// 	t_elements 	element;
// //	t_amb_light amb;
// 	int	i;

// 	element = *data->elements;
// //	amb = element->amb_light;
// 	i = 0;
// 	element.ambient_light_count += 1;
// 	if (element.ambient_light_count > 1)
// 	{
// 		printf("Error/n");
// 		printf("Only one ambient light declaration allowed./n");
// 		exit (1);
// 	}
//	amb->

/*
	identifier: A
∗ ambient lighting ratio in range [0.0,1.0]: 0.2
∗ R,G,B colors in range [0-255]: 255, 255, 255
*/

// }

int	open_file(char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0); //TODO- Error messaga for file opening
	return (fd);
}

int	check_input(char **argv, t_data *data)
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
			return (0);//TODO- Error message for parsing
		}
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
	if (check_count(data))
		return (1);
	else
		return (0);
	//use get_next line to fill array with objects
}

int	load_input(int argc, char **argv, t_data *data)
{
	int 	len;

	if (argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 3], ".rt", 3) != 0)
		return (0);
	if (!check_input(argv, data))
	{
		printf("check your input\n");
		exit(0);
	}
	return (1);

}

void init(t_data *data)
{
	t_counter *counter;

	data->counter = malloc(sizeof(t_counter));
	counter = data->counter;
	counter->ambient_light_count = 0;
	counter->light_count = 0;
	counter->camera_count = 0;
	counter->sphere_count = 0;
	counter->cylinder_count = 0;
	counter->plane_count = 0;
	counter->newline_count = 0;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
//	data.img = 
//	data = NULL;
	init(data);
	return (load_input(argc, argv, data));

	// data = load_input(argc, argv);
	// data->win_ptr =mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");

}
