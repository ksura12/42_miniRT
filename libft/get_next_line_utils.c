/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:23:53 by kaheinz           #+#    #+#             */
/*   Updated: 2022/05/29 02:02:47 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	finding_newline(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*stringjoin(char *s1, char *s2)
{
	char	*concatenated;
	int		lens1;
	int		lens2;

	lens1 = ftt_strlen(s1);
	lens2 = ftt_strlen(s2);
	concatenated = malloc(lens1 + lens2 + 1);
	if (!concatenated)
	{
		free(concatenated);
		return (NULL);
	}
	if (concatenated)
	{
		ftt_memcpy(concatenated, s1, lens1);
		ftt_memcpy(concatenated + lens1, s2, lens2 + 1);
	}
	free(s1);
	return (concatenated);
}

size_t	ftt_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ftt_memcpy(void *dst, void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
		*(unsigned char *)(dst + i++) = *(unsigned char *)(src++);
	return (dst);
}
