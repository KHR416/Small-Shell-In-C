/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:28:34 by chakim            #+#    #+#             */
/*   Updated: 2025/01/08 15:20:17 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_path = check_cmd(paths[i], cmd);
		if (cmd_path)
		{
			free_paths(paths);
			return (cmd_path);
		}
		i++;
	}
	free_paths(paths);
	return (NULL);
}

char	*check_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	**prepare_cmd_args(char *cmd)
{
	char	**cmd_args;

	if (!cmd || !*cmd)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		exit(1);
	if (!cmd_args[0])
	{
		free_paths(cmd_args);
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	return (cmd_args);
}

void	exe_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	cmd_args = prepare_cmd_args(cmd);
	if (access(cmd_args[0], X_OK) == 0)
		path = ft_strdup(cmd_args[0]);
	else
		path = find_path(cmd_args[0], envp);
	if (!path)
	{
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_paths(cmd_args);
		exit(127);
	}
	if (execve(path, cmd_args, envp) == -1)
	{
		free(path);
		free_paths(cmd_args);
		perror("execve");
		exit(126);
	}
}
