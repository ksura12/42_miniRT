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
