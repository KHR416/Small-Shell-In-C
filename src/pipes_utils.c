/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:54:37 by chakim            #+#    #+#             */
/*   Updated: 2025/01/07 19:11:38 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"
#include "minishell.h"

void	init_pipes(t_pipes *pipes, t_msvar *var)
{
	int	i;

	i = 0;
	pipes->cmd_count = var->argc - 3;
	pipes->pipe_count = pipes->cmd_count - 1;
	pipes->pipes = (int **)malloc(sizeof(int *) * pipes->pipe_count);
	while (i < pipes->pipe_count)
	{
		pipes->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes->pipes[i])
		{
			free_pipes(pipes, i);
			exit(1);
		}
		i++;
	}
	pipes->pids = (pid_t *)malloc(sizeof(pid_t) * pipes->cmd_count);
	if (!pipes->pids)
	{
		free(pipes->pipes);
		exit(1);
	}
}

void	destroy_pipes(t_pipes *pipes)
{
	int	i;

	i = 0;
	if (pipes->pipes)
	{
		while (i < pipes->pipe_count)
		{
			if (pipes->pipes[i])
			{
				close(pipes->pipes[i][0]);
				close(pipes->pipes[i][1]);
				free(pipes->pipes[i]);
			}
			i++;
		}
		free(pipes->pipes);
	}
	if (pipes->pids)
		free(pipes->pids);
}

void	free_pipes(t_pipes *pipes, int i)
{
	int	count;

	count = 0;
	while (count < i)
		free(pipes->pipes[count++]);
	free(pipes->pipes);
}

void	close_pipes(t_pipes *pipes, int except_index)
{
	int	i;

	i = 0;
	while (i < pipes->pipe_count)
	{
		if (i != except_index)
		{
			close(pipes->pipes[i][0]);
			close(pipes->pipes[i][1]);
		}
		i++;
	}
}
