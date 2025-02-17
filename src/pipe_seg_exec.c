/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seg_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:47:47 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/17 15:20:11 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_seg.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void	pipe_seg_exec(t_pipe_seg *ps, t_msvar *msvar)
{
	size_t	pipe_cnt;
	size_t	cpid_cnt;
	int		wstatus;
	pid_t	*cpids;
	int		pipefd[2];

	pipe_cnt = ft_lstsize(ps->ceu_list) - 1;
	cpid_cnt = ft_lstsize(ps->ceu_list);
	cpids = malloc(sizeof(pid_t) * cpid_cnt);
	if (!cpids)
		exit(1);
	size_t	i = 0;
	for (t_list *it = ps->ceu_list; it; ++i)
	{
		if (i < pipe_cnt)
			pipe(pipefd);
		cpids[i] = fork();
		if (!cpids[i])
		{
			free(cpids);
			if (i < pipe_cnt)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			t_ceu	*ceu = it->content;
			free(it);
			ceu_exec(ceu, msvar);
		}
		if (i < pipe_cnt)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		t_list	*temp = it;
		it = it->next;
		ft_lstdelone(temp, destroy_ceu);
	}
	for (i = 0; i < cpid_cnt; ++i)
		waitpid(cpids[i], &wstatus, 0);
	free(cpids);
	free(ps);
	free_msvar(msvar);
	exit(wstatus);
}
