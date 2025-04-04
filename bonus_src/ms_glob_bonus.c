/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:34:51 by chakim            #+#    #+#             */
/*   Updated: 2025/04/04 17:43:30 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_glob.h"
#include "generic_array.h"
#include "ms_def.h"
#include "wrapper.h"
#include <stdlib.h>
#include <dirent.h>

static int	update_string(char **string, char *pattern, int glob_flag)
{
	char	*matched;

	if (glob_flag)
	{
		glob_flag = 0;
		matched = ft_strnstr(*string, pattern, ft_strlen(*string));
		if (!matched)
			return (FAILURE);
		*string = matched + ft_strlen(pattern);
	}
	else
	{
		if (ft_strncmp(*string, pattern, ft_strlen(pattern)))
			return (FAILURE);
		*string += ft_strlen(pattern);
	}
	return (SUCCESS);
}

static int	ms_fnmatch(char **patterns, char *string)
{
	char	*last_pat;
	int		glob_flag;

	last_pat = NULL;
	glob_flag = 0;
	while (*patterns)
	{
		if (!**patterns)
			glob_flag = 1;
		else
		{
			last_pat = *patterns;
			if (update_string(&string, last_pat, glob_flag))
				return (FAILURE);
			glob_flag = 0;
		}
		++patterns;
	}
	if (glob_flag)
		return (SUCCESS);
	if (!ft_strcmp(string + ft_strlen(string) - ft_strlen(last_pat), last_pat))
		return (SUCCESS);
	return (FAILURE);
}

static char	**ms_glob_helper(DIR *dir, char **patterns, int is_hidden)
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
			if (append_gen_arr(files, ent->d_name, ft_strdup_wrap))
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
