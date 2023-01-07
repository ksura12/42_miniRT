/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:25:53 by kaheinz           #+#    #+#             */
/*   Updated: 2023/01/07 09:19:29 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/structs.h"
#include	"../header/minirt.h"

/**
 * @brief checks if the give char ** hold the expected amount of
 * words
 * 
 * @param expected integer number of words
 * @param words char ** holding words
 * @return int returns 1 on succes, 0 on failure
 */
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

/**
 * @brief check if color values input from file
 * are smaler than 256
 * 
 * @param rgb parsed part of .rt fiel containing rgb value
 * @param location destination to store rgb values in
 * @return int return 1 on succes, 0 on failure
 */
int	check_colors(char *rgb, t_color *location)
{
	char	**colors;

	colors = ft_split(rgb, ',');
	if (!expected_words(3, colors) || !isaldigit(colors))
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
	location->t = 0;
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
			if (!ft_isdigit(value[j][i]) && value[j][i] != '\n')
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

static void	char_to_double_2(char	**splitted, double *result, double *dst)
{
	int	i;

	i = 0;
	while (splitted[1][i])
		i++;
	if (ft_atoi(splitted[0]) < 0 || splitted[0][0] == '-')
		*result = ft_atoi(splitted[0]) + -1 * pow(0.1, i) \
			* ft_atoi(splitted[1]);
	else
		*result = 1 * ft_atoi(splitted[0]) + pow(0.1, i) \
			* ft_atoi(splitted[1]);
	freeing_dpointer(splitted);
	*dst = *result;
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
		char_to_double_2(splitted, &result, dst);
		return (1);
	}
	freeing_dpointer(splitted);
	return (0);
}

int	isequal(float a, float b)
{
	return ((a - 0.00001 <= b) && (a + 0.00001 >= b));
}
