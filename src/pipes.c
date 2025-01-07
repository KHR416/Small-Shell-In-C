/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:25:23 by chakim            #+#    #+#             */
/*   Updated: 2025/01/07 19:09:52 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"
#include "minishell.h"

static void	create_pipes(t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->pipe_count)
	{
		if (pipe(pipes->pipes[i]) == -1)
		{
			perror("pipes");
			free_pipes(pipes, i);
			exit(1);
		}
		i++;
	}
}

static void	create_processes(t_pipes *pipes, t_msvar *var)
{
	int	i;

	i = 0;
	while (i < pipes->cmd_count)
	{
		pipes->pids[i] = fork();
		if (pipes->pids[i] == -1)
		{
			perror("fork");
			destoy_pipes(pipes);
			exit(1);
		}
		if (pipes->pids[i] == 0)
			child_process(pipes, i, var);
		if (i > 0)
			close(pipes->pipes[i - 1][0]);
		if (i < pipes->pipe_count)
			close(pipes->pipes[i][1]);
		i++;
	}
}

void	handling_pipes(t_msvar *var)
{
	t_pipes	pipes;
	int		status;
	int		i;

	init_pipes(&pipes, var);
	create_pipes(&pipes);
	create_processes(&pipes, var);
	i = 0;
	while (i < pipes.cmd_count)
	{
		waitpid(pipes.pids[i], &status, 0);
		i++;
	}
	destroy_pipes(&pipes);
}
