/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:34:51 by chakim            #+#    #+#             */
/*   Updated: 2025/03/05 13:21:47 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_glob.h"

int	ms_fnmatch(char **pattern, char *string)
{
	char	*p;
	char	*n;
	int		i;

	i = 0;
	while (pattern[i] != NULL)
	{
		p = pattern[i];
		n = string;
		while (*p != '\0')
		{
			if (*p == '*')
			{
				while (*p == '*')
					++p;
				if (*p == '\0')
					return (EXIT_SUCCESS);
				while (*n != '\0')
				{
					if (ms_fnmatch(&p, n) == 0)
						return (EXIT_SUCCESS);
					++n;
				}
				return (EXIT_FAILURE);
			}
			else
			{
				if (*p != *n)
					return (EXIT_FAILURE);
				++p;
				++n;
			}
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

int	is_external_dir(char **pattern)
{
	int	i;

	i = 0;
	while (pattern[i] != NULL)
	{
		if (ft_strchr(pattern[i], '/') != 0)
			return (1);
		++i;
	}
	return (0);
}

char	**ms_glob(char **pattern)
{
	DIR 			*dir;
	struct dirent	*ent;
	char			**files;
	int				i;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	files = NULL;
	i = 0;
	if (is_external_dir(pattern))
		return (NULL);
	while (1)
	{
		ent = readdir(dir);
        if (ent == NULL)
            break;
		if (ft_strncmp(ent->d_name, ".", 1) == 0)
			continue ;
		if (ms_fnmatch(pattern, ent->d_name) == 0)
		{
			files = ft_realloc(files, sizeof(char *) * i, sizeof(char *) * (i + 2));
			files[i] = ft_strdup(ent->d_name);
			++i;
		}
	}
	closedir(dir);
	if (files == NULL)
		return (NULL);
	files[i] = NULL;
	return (files);
}