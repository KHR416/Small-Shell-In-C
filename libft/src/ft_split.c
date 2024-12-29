/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:32:53 by wchoe             #+#    #+#             */
/*   Updated: 2024/12/30 02:03:55 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	substrlen(const char *s, char c)
{
	char	*temp_s;

	temp_s = (char *)s;
	while (*temp_s && *temp_s != c)
		++temp_s;
	return (temp_s - s);
}

static size_t	count_substr(const char *s, char c)
{
	size_t	substr_count;

	substr_count = 0;
	while (*s)
	{
		while (*s && *s == c)
			++s;
		if (*s)
			++substr_count;
		s += substrlen(s, c);
	}
	return (substr_count);
}

static void	delete_splitted(char **split)
{
	size_t	spl_idx;

	spl_idx = 0;
	while (split[spl_idx] != NULL)
		free(split[spl_idx++]);
	free(split);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	size_t	spl_idx;

	split = (char **)malloc(sizeof(char *) * (count_substr(s, c) + 1));
	if (split == NULL)
		return (NULL);
	spl_idx = 0;
	while (*s)
	{
		while (*s && *s == c)
			++s;
		if (*s)
		{
			split[spl_idx] = ft_substr(s, 0, substrlen(s, c));
			if (split[spl_idx] == NULL)
			{
				delete_splitted(split);
				return (NULL);
			}
			++spl_idx;
		}
		s += substrlen(s, c);
	}
	split[spl_idx] = NULL;
	return (split);
}
