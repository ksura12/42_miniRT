#include	"../header/structs.h"
#include	"../header/minirt.h"

int	expected_words(int expected, char **words)
{
	int	i;

	i = 0;
	while (words[i] && words[i][0] != '\n')
		i++;
	if (i == expected)
		return (1);
	else
		return (0);
}

int	open_file(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0); //TODO- Error messaga for file opening
	return (fd);
}

int	check_colors(char *rgb, t_color *location)
{
	char	**colors;

	colors = ft_split(rgb, ',');
	if (!expected_words(3, colors))
		return (0);
	if (ft_atoi(colors[0]) <= 255 && ft_atoi(colors[0]) >= 0)
		location->r = ft_atoi(colors[0]);
	else
		return (0);
	if (ft_atoi(colors[1]) <= 255 && ft_atoi(colors[1]) >= 0)
		location->b = ft_atoi(colors[1]);
	else
		return (0);
	if (ft_atoi(colors[2]) <= 255 && ft_atoi(colors[2]) >= 0)
		location->g = ft_atoi(colors[2]);
	else
		return (0);
	freeing_dpointer(colors);
	return (1);
}

/**
 * @brief check if the given char* poiunt to an all digit string 
 * with a leading + or -
 * 
 * @param value pointer to the string to test
 * @return int 0 for testing false, 1 if everything are digits
 */
int	isaldigit(char **value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (value[0][0] == '-' || value[0][0] == '+' )
		i++;
	while (value[j])
	{
		if (j != 0)
			i = 0;
		while (value[j][i])
		{
			if (!ft_isdigit(value[j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

/**
 * @brief casts a char * to a double value, checks for wrong input
 * 
 * @param value original char *
 * @param dst pointer to the double value destination
 * @return int 0 for unsuccessfull casting, 1 for successfull
 * creation of double value
 */
int	char_to_double(char *value, double *dst)
{
	double	result;
	char	**splitted;
	int		i;

	splitted = ft_split(value, '.');
	if (expected_words(1, splitted) && isaldigit(splitted))
	{
		result = ft_atoi(splitted[0]);
		freeing_dpointer(splitted);
		*dst = result;
		return (1);
	}
	else if (expected_words(2, splitted) && isaldigit(splitted))
	{
		i = 0;
		while (splitted[1][i])
			i++;
		result = 1 * ft_atoi(splitted[0]) + pow(0.1, i) * ft_atoi(splitted[1]);
		freeing_dpointer(splitted);
		*dst = result;
		return (1);
	}
	freeing_dpointer(splitted);
	return (0);
}
