/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:13:32 by chakim            #+#    #+#             */
/*   Updated: 2025/01/07 19:19:41 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"
#include "minishell.h"

static int	setup_input_and_redirection(t_pipes *pipes, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
			return (-1);
	}
	if (dup2(fd, 0) == -1 || dup2(pipes->pipes[0][1], 1) == -1)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

static void	first_process(t_pipes *pipes, int i, t_msvar *var)
{
	int	fd;

	fd = setup_input_and_redirection(pipes, var->argv[1]);
	if (fd == -1)
	{
		destroy_pipes(pipes);
		exit(1);
	}
	close(fd);
	close_pipes(pipes, 0);
	destroy_pipes(pipes);
	exe_cmd(var->argv[i + 2], var->envp);
}

static void	last_process(t_pipes *pipes, int i, t_msvar *var)
{
	int	fd;

	fd = open(var->argv[var->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(var->argv[var->argc - 1]);
		destroy_pipes(pipes);
		exit(1);
	}
	if (dup2(pipes->pipes[pipes->pipe_count - 1][0], 0) == -1)
	{
		close(fd);
		destroy_pipes(pipes);
		exit(1);
	}
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		destroy_pipes(pipes);
		exit(1);
	}
	close(fd);
	close_pipes(pipes, pipes->pipe_count - 1);
	destroy_pipes(pipes);
	exe_cmd(var->argv[i + 2], var->envp);
}

static void	middle_process(t_pipes *pipes, int i, t_msvar *var)
{
	if (dup2(pipes->pipes[i - 1][0], 0) == -1)
	{
		destroy_pipes(pipes);
		exit(1);
	}
	if (dup2(pipes->pipes[i][1], 1) == -1)
	{
		destroy_pipes(pipes);
		exit(1);
	}
	close_pipes(pipes, i - 1);
	close_pipes(pipes, i);
	close(pipes->pipes[i][1]);
	destroy_pipes(pipes);
	exe_cmd(var->argv[i + 2], var->envp);
}

void	child_process(t_pipes *pipes, int i, t_msvar *var)
{
	if (i == 0)
		first_process(pipes, i, var);
	else if (i == pipes->cmd_count - 1)
		last_process(pipes, i, var);
	else
		middle_process(pipes, i, var);
	exit(1);
}
