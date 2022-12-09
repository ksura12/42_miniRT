
#include "../header/minirt.h"



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
