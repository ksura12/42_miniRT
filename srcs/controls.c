#include	"../header/structs.h"
#include	"../header/minirt.h"

int	close_win(void *param);
int	key_press(int keycode, void *param);

void	controls(t_data *data)
{
	mlx_hook(data->mlx_win, RED_CROSS, 0, close_win, data);
	mlx_hook(data->mlx_win, KEY_PRESS, 0, key_press, data);
}

int	key_press(int keycode, void *param)
{
//	t_data	*data;

//	data = (t_data *)param;
	(void)param;
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

int	close_win(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
}
