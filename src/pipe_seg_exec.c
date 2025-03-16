/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seg_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:47:47 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/15 20:46:10 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_seg.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// int	pipe_seg_exec(t_pipe_seg **ps, t_msvar *msvar)
// {
// 	size_t	pipe_cnt;
// 	size_t	cpid_cnt;
// 	size_t	arr_len;
// 	int		wstatus = 255;
// 	pid_t	*cpids;
// 	int		pipefd[2];

// 	arr_len = 0;
// 	while (ps[arr_len])
// 		++arr_len;
// 	if (arr_len <= 1)
// 	{
// 		if (ps[0]->type == PS_CEU)
// 		{
// 			int	exit_status = ceu_exec(ps[0]->data.ceu, msvar, 0);
// 			restore_ttydup(msvar);
// 			return (exit_status);
// 		}
// 		else
// 		{
// 			int	exit_status = ast_traversal(ps[0]->data.ast, msvar);
// 			restore_ttydup(msvar);
// 			return (exit_status);
// 		}
// 	}
// 	pipe_cnt = arr_len - 1;
// 	cpid_cnt = arr_len;
// 	cpids = malloc(sizeof(pid_t) * cpid_cnt);
// 	if (!cpids)
// 	{
// 		perror("malloc");
// 		return (EXIT_FAILURE);
// 	}
// 	size_t  i = 0;
// 	for (; ps[i]; ++i)
// 	{
// 		if (i < pipe_cnt)
// 		{
// 			if (pipe(pipefd) == -1)
// 			{
// 				perror("pipe");
// 				free(cpids);
// 				return (EXIT_FAILURE);
// 			}
// 		}
// 		cpids[i] = fork();
// 		if (cpids[i] == -1)
// 		{
// 			perror("fork");
// 			free(cpids);
// 			while (i--)
// 				wait(NULL);
// 			return (EXIT_FAILURE);
// 		}
// 		if (!cpids[i])
// 		{
// 			free(cpids);
// 			clear_ttydup(msvar);
// 			if (i < pipe_cnt)
// 			{
// 				close(pipefd[0]);
// 				dup2(pipefd[1], STDOUT_FILENO);
// 				close(pipefd[1]);
// 			}
// 			if (ps[i]->type == PS_CEU)
// 			{
// 				int	exit_status = ceu_exec(ps[i]->data.ceu, msvar, 1);
// 				clear_msvar(msvar);
// 				exit(exit_status);
// 			}
// 			else
// 			{
// 				int	exit_status = ast_traversal(ps[i]->data.ast, msvar);
// 				clear_msvar(msvar);
// 				exit(exit_status);
// 			}
// 		}
// 		if (i < pipe_cnt)
// 		{
// 			close(pipefd[1]);
// 			dup2(pipefd[0], STDIN_FILENO);
// 			close(pipefd[0]);
// 		}
// 	}
// 	restore_ttydup(msvar);
// 	for (i = 0; i < cpid_cnt; ++i)
// 		waitpid(cpids[i], &wstatus, 0);
// 	free(cpids);
// 	if (WIFSIGNALED(wstatus))
// 		return (128 + WTERMSIG(wstatus));
// 	return (WEXITSTATUS(wstatus));
// }
