/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:34:51 by chakim            #+#    #+#             */
/*   Updated: 2025/04/03 21:13:48 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_glob.h"
#include "generic_array.h"
#include "ms_def.h"

int	ms_fnmatch(char **patterns, char *string)
{
	char	*matched;
	size_t	i;

	i = 0;
	while (patterns[i])
	{
		if (i > 0 && !*patterns[i - 1])
		{
			matched = ft_strnstr(string, patterns[i], ft_strlen(string));
			if (!matched)
				return (FAILURE);
			string = matched + ft_strlen(patterns[i]);
		}
		else if (*patterns[i])
		{
			if (ft_strncmp(string, patterns[i], ft_strlen(patterns[i])))
				return (FAILURE);
			string += ft_strlen(patterns[i]);
		}
		++i;
	}
	if (i > 0 && *patterns[i - 1] && *string)
		return (FAILURE);
	return (SUCCESS);
}

void	*my_strdup(void *str)
{
	return (ft_strdup(str));
}

char	**ms_glob_helper(DIR *dir, char **patterns, int is_hidden)
{
	struct dirent	*ent;
	t_gen_arr		*files;

	files = create_gen_arr();
	while (1)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if ((is_hidden && *ent->d_name != '.') || \
		(!is_hidden && *ent->d_name == '.'))
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

char	**ms_glob(char **patterns)
{
	DIR	*dir;
	int	is_hidden;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	is_hidden = 0;
	if (**patterns == '.')
		is_hidden = 1;
	return (ms_glob_helper(dir, patterns, is_hidden));
}
