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
