/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/03/15 23:32:27 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_error_checker(char **args)
{
	char *path;

	path = args[1];
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (FAILURE);
	}
	if (access(args[1], F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (access(args[1], R_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	return (SUCCESS);
}

static char	*set_to_parent_dir(char *abs_path)
{
	char	*result;
	size_t	diff;
	char	*last_slash;

	if (!abs_path)
		return (NULL);
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
	if (ft_strcmp(args[1], "..") == 0)
		return (2);
	return (0);
}

int	ms_cd(char **args, char ***envp, t_buf *buf)
{
	char	*abs_path;
	int		error_code;
	int		dot_case;
	char	*old_pwd;

	if (!args[1])
		return (SUCCESS);
	dot_case = how_many_dots(args);
	if (dot_case == 0)
	{
		error_code = cd_error_checker(args);
		if (error_code != SUCCESS)
			return (error_code);
	}
	if (dot_case == 1)
		abs_path = ms_getcwd(buf);
	else if (dot_case == 2)
		abs_path = set_to_parent_dir(ms_getcwd(buf));
	else
		abs_path = ft_strdup(args[1]);
	if (!abs_path)
		return (FAILURE);
	old_pwd = ms_getcwd(buf);
	if (!old_pwd)
	{
		free(abs_path);
		return (FAILURE);
	}
	ms_setenv("OLDPWD", old_pwd, envp, buf);
	free(old_pwd);
	if (chdir(abs_path) == -1)
	{
		perror("minishell: cd");
		free(abs_path);
		return (FAILURE);
	}
	free(abs_path);
	ms_setenv("PWD", ms_getcwd(buf), envp, buf);
	return (SUCCESS);
}
