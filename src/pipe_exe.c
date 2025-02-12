/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:48:26 by chakim            #+#    #+#             */
/*   Updated: 2025/02/12 17:12:22 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ceu.h"
#include "pipe_seg.h"
#include "minishell.h"
#include "sys/types.h"

void	close_fd_if_valid(int fd) 
{
	if (fd > 0)
		close(fd);
}

int	execute_child_process(t_ceu *ceu, t_msvar *var, int pipefd[2], size_t i, size_t pipe_cnt) 
{
	int exe_result;

	exe_result = ceu_exec(ceu, var);
	if (i < pipe_cnt)
	{
		close_fd_if_valid(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (FAILURE);
		}
		close_fd_if_valid(pipefd[1]);
	}
	return (exe_result);
}

void pipe_exe(t_pipe_seg *ps, t_msvar *var)
{
	size_t	pipe_cnt;
	size_t	cpid_cnt;
	int		wstatus;
	pid_t	*cpids;
	int		pipefd[2];
	int		error_flag;

	error_flag = 0;
	pipe_cnt = ft_lstsize(ps->ceu_list) - 1;
	cpid_cnt = ft_lstsize(ps->ceu_list);
	cpids = malloc(sizeof(pid_t) * cpid_cnt);
	if (!cpids)
		exit(FAILURE);
	size_t	i = 0;
	t_list *it = ps->ceu_list;
	for (; it != NULL && !error_flag; it = it->next)
	{
		if (i < pipe_cnt)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				error_flag = 1;
				continue ;
			}
		}
		cpids[i] = fork();
		if (cpids[i] == -1)
		{
			perror("fork");
			error_flag = 1;
			close_fd_if_valid(pipefd[0]);
			close_fd_if_valid(pipefd[1]);
			continue ;
		}
		else if (cpids[i] == 0)
		{
			int exe_result;

			exe_result = \
			execute_child_process(it->content, var, pipefd, i, pipe_cnt);
			exit(exe_result);
		}
		else
		{
			if (i < pipe_cnt)
			{
				close_fd_if_valid(pipefd[1]);
				if (dup2(pipefd[0], 0) == -1)
				{
					perror("dup2");
					error_flag = 1;
				}
				close_fd_if_valid(pipefd[0]);
			}
		}
	}
	it = ps->ceu_list;
	while (it)
	{
		t_list *temp;
		temp = it;
		it = it->next;
		ft_lstdelone(temp, destroy_ceu);
	}
	for (size_t j = 0; j < i; ++j)
	{
		if (cpids[i] > 0)
		{
			if (waitpid(cpids[j], &wstatus, 0) == -1) 
                perror("waitpid");
		}
	}
	free(cpids);
	free(ps);
	if (error_flag)
		return (FAILURE);
	if (WIFEXITED(wstatus))
    	return (WEXITSTATUS(wstatus));
	return (FAILURE);
}
