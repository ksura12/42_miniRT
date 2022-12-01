
#include	"../header/structs.h"
#include	"../header/minirt.h"

int	check_input(int argc, char **argv)
{
	int len;

	if(argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 3], ".rt", 3) != 0)
		return (0);
	return (1);
}

int	load_input(int argc, char **argv)
{
	if (!check_input(argc, argv))
	{
		printf("check your input\n");
		exit(0);
	}
	return (1);

}

int	main(int argc, char **argv)
{
	return (load_input(argc, argv));
	// t_data	*data;
	// data = load_input(argc, argv);
	// data->win_ptr =mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");

}