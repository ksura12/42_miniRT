/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:33:43 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/09 14:15:12 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/structs.h"
#include	"../header/minirt.h"

int	parsing_line(char *line, t_data *data)
{
	char	**splitted;
	t_counter *counter;
	int		i;

	i = 0;
	counter = data->counter;
	splitted = ft_split(line, ' ');
	while (splitted[i])
	{
		printf("splitted line = %s\n", splitted[i]);
		if (splitted[i][0] == '\n')
			break ;
		i++;
	}
	if (!ft_strncmp(splitted [0], "A\0", 2))
		counter->ambient_light_count += 1;
	else if (!ft_strncmp(splitted [0], "C\0", 2))
		counter->camera_count += 1;
	else if (!ft_strncmp(splitted [0], "L\0", 2))
		counter->light_count += 1;
	else if (!ft_strncmp(splitted [0], "sp\0", 3))
		counter->sphere_count += 1;
	else if (!ft_strncmp(splitted [0], "cy\0", 3))
		counter->cylinder_count += 1;
	else if (!ft_strncmp(splitted [0], "pl\0", 3))
		counter->plane_count += 1;
	else
	{
		printf("ERROR, unidentified element.\n");
		return (1);
	}
	return (0);
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

int	check_input(char **argv, t_data *data)
{
	int		fd;
	char	*line;

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
		line = get_next_line(fd);
	}
	printf("Number of A %i\n", data->counter->ambient_light_count);
	printf("Number of C %i\n", data->counter->camera_count);
	printf("Number of cy %i\n", data->counter->cylinder_count);
	//use get_next line to fill array with objects
	close(fd);
	return (1);
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
