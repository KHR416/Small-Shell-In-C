/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/03/01 22:08:18 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_error_checker(char **args)
{
	if (args[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (FAILURE);
	}
	if (access(args[1], F_OK) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[1]);
		return (127);
	}
	else if (access(args[1], R_OK) == -1)
	{
		printf("minishell: cd: %s: Permission denied\n", args[1]);
		return (126);
	}
	return (SUCCESS);
}

static char	*set_to_parent_dir(char *abs_path)
{
	char	*result;
	size_t	diff;
	char	*last_slash;

	last_slash = ft_strrchr(abs_path, '/');
	if (last_slash == abs_path)
		diff = 1;
	else
		diff = (size_t)(last_slash - abs_path);
	result = ft_substr(abs_path, 0, diff);
	free(abs_path);
	return (result);
}

static int	how_many_dots(char **args)
{
	if (ft_strcmp(args[1], ".") == 0)
		return (1);
	else if (ft_strcmp(args[1], "..") == 0)
		return (2);
	else
		return (0);
}

/*
	this fuction go to absolute directory if it's valid.
	If there is an error, return FAILURE.
	cd .. goes to parent directory. Otherwise, it goes to absolute directory
*/
int	ms_cd(char **args)
{
	char	*abs_path;
	int		error_code;

	abs_path = NULL;
	error_code = 0;
	if (!args[1])
		return (SUCCESS);
	if (!how_many_dots(args))
	{
		error_code = cd_error_checker(args);
		if (error_code != SUCCESS)
			return (error_code);
	}
	if (how_many_dots(args) == 1)
		abs_path = ms_getcwd();
	else if (how_many_dots(args) == 2)
	{
		abs_path = ms_getcwd();
		abs_path = set_to_parent_dir(abs_path);
	}
	else
		abs_path = ft_strdup(args[1]);
	if (!abs_path)
		return (FAILURE);
	if (chdir(abs_path) == -1)
	{
		free(abs_path);
		return (FAILURE);
	}
	free(abs_path);
	return (SUCCESS);
}
