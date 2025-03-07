/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:01:45       by                   #+#    #+#             */
/*   Updated: 2025/03/06 13:01:45 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_glob.h"
#include "generic_array.h"
#include "ms_def.h"

int	ms_fnmatch(char **patterns, char *string)
{
	char	*matched;

    while (*patterns)
    {
		if (**patterns)
		{
			matched = ft_strnstr(string, *patterns, ft_strlen(string));
			if (!matched)
				return (FAILURE);
			string = matched + ft_strlen(*patterns);
		}
		++patterns;
    }
    return (SUCCESS);
}

void	*my_strdup(void *str)
{
	return (ft_strdup(str));
}

char	**ms_glob(char **patterns)
{
	DIR				*dir;
	struct dirent	*ent;
	t_gen_arr		*files;
	int				is_hidden;

	files = create_gen_arr();
	dir = opendir(".");
	if (**patterns == '.')
		is_hidden = 1;
	else
		is_hidden = 0;
	while (1)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if ((is_hidden && *ent->d_name != '.') || (!is_hidden && *ent->d_name == '.'))
			continue ;
		if (!ms_fnmatch(patterns, ent->d_name))
		{
			if (append_gen_arr(files, ent->d_name, my_strdup))
			{
				closedir(dir);
				destroy_gen_arr(files, free);
				return (NULL);
			}
		}
	}
	closedir(dir);
	return ((char **)detach_gen_arr(files));
}
