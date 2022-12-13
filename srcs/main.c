#include	"../header/structs.h"
#include	"../header/minirt.h"


void	mlx_handle(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bit_per_pix, &data->line_len, &data->endian);
	controls(data);
	
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_loop(data->mlx);
}


int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	// mlx_handle(data);
	parsing(argc, argv, data);
	free_allocation_objects(data);
	return (0);
}
