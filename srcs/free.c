/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:22:50 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 05:22:53 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

void	free_allocation(t_data *data)
{
	free(data->elements->light);
	free(data->elements->camera);
	free(data->elements->amb_light);
	free(data->elements);
	free(data->counter);
	free(data);
}

void	free_allocation_objects(t_data *data)
{
	int			i;
	t_counter	*counter;
	int			obj_cont;

	counter = data->counter;
	obj_cont = counter->cylinder_count + counter->plane_count
		+ counter->sphere_count;
	free(data->elements->light);
	free(data->elements->camera->camtoworld);
	free(data->elements->camera);
	free(data->elements->amb_light);
	i = 0;
	while (i < obj_cont)
	{
		free(data->elements->objects[i]);
		i++;
	}
	free(data->elements->objects);
	free(data->elements);
	free(data->counter);
	free(data);
}

void	freeing_dpointer(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (paths[i] != NULL && ft_strncmp(paths[i], "", 1) != 0)
		{
			free(paths[i]);
		}
		i++;
	}
	free (paths);
}
