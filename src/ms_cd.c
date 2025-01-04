/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/01/04 21:22:20 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_args.h"
#include "minishell.h"

/*
	this fuction go to absolute directory if it's valid.
	If there is an error, return FAILURE.
	cd .. goes to parent directory. Otherwise, it goes to absolute directory
*/

static int	cd_error_checker(char **args)
{
	if (args[2])
	{
		printf("bash: cd: too many arguments\n");
		return (FAILURE);
	}
	if (access(args[1], F_OK) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", args[1]);
		return (127);
	}
	else if (access(args[1], R_OK) == -1)
	{
		printf("bash: cd: %s: Permission denied\n", args[1]);
		return (126);
	}
	return (SUCCESS);
}

static char	*set_to_parent_dir(char *abs_path)
{
	char 	*result;
	size_t	diff;

	diff = (size_t)(abs_path - ft_strrchr(abs_path, '/'));
	result = ft_substr(abs_path, 0, diff);
	free(abs_path);
	return (result);
}

int	ms_cd(char **args)
{
	char	*abs_path;

	if (cd_error_checker(args) && (args[1] != '.' || args[1] != '..'))
		return (cd_error_checker(args));
	if (args[1] == '.')
		abs_path = ms_getcwd();
	else if (args[1] == '..')
		abs_path = set_to_parent_dir(abs_path);
	else
		abs_path = args[1];
	if (!abs_path)
		return (NULL);
	if (chdir(abs_path) == -1)
	{
		free(abs_path);
		return (FAILURE);
	}
	free(abs_path);
	return (SUCCESS);
}
