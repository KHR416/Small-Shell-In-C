/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seg_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:47:47 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/24 19:01:14 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_seg.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int	pipe_seg_exec(t_pipe_seg *ps, t_msvar *msvar)
{
	size_t	pipe_cnt;
	size_t	cpid_cnt;
	int		wstatus = 255;
	pid_t	*cpids;
	int		pipefd[2];

	pipe_cnt = ft_lstsize(ps->ceu_list) - 1;
	cpid_cnt = ft_lstsize(ps->ceu_list);
	cpids = malloc(sizeof(pid_t) * cpid_cnt);
	if (!cpids)
	{
		perror("malloc");
		return (EXIT_FAILURE);
	}
	size_t  i = 0;
	for (t_list *it = ps->ceu_list; it; ++i)
	{
		if (i < pipe_cnt)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				free(cpids);
				return (EXIT_FAILURE);
			}
		}
		cpids[i] = fork();
		if (cpids[i] == -1)
		{
			perror("fork");
			free(cpids);
			return (EXIT_FAILURE);
		}
		if (!cpids[i])
		{
			if (i < pipe_cnt)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			int	exit_status = ceu_exec(it->content, msvar);
			free(cpids);
			return (exit_status);
		}
		if (i < pipe_cnt)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		it = it->next;
	}
	for (i = 0; i < cpid_cnt; ++i)
		waitpid(cpids[i], &wstatus, 0);
	free(cpids);
	return (WEXITSTATUS(wstatus));
}
