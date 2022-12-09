
#include "../header/minirt.h"



void	freeing_dpointer(void **paths)
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
