/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traversal_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/27 17:54:43 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>
#include "generic_array.h"
#include "stack.h"
#include <sys/wait.h>

int	execute_ceu(t_ast *node, t_msvar *msvar, int pipe_flag)
{
	return (ceu_exec(node->data[0].ceu, msvar, pipe_flag));
}

static void	execute_child(
				t_ast *node,
				t_msvar *msvar,
				int pipefd[2],
				int is_left)
{
	int	exit_status;

	if (is_left)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	exit_status = ast_traversal(node, msvar, 1);
	clear_msvar(msvar);
	exit(exit_status);
}

static int	handle_pipe(t_ast *node, t_msvar *msvar)
{
	int		pipefd[2];
	pid_t	cpid_left;
	pid_t	cpid_right;
	int		wstatus;

	if (pipe(pipefd) < 0)
		return (EXIT_FAILURE);
	cpid_left = fork();
	if (cpid_left < 0)
		return (EXIT_FAILURE);
	if (!cpid_left)
		execute_child(node->data[0].ast, msvar, pipefd, 1);
	cpid_right = fork();
	if (cpid_right < 0)
		return (waitpid(cpid_left, NULL, 0), EXIT_FAILURE);
	if (!cpid_right)
		execute_child(node->data[1].ast, msvar, pipefd, 0);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(cpid_left, NULL, 0);
	waitpid(cpid_right, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (WEXITSTATUS(wstatus));
}

static int	handle_logic(t_ast *node, t_msvar *msvar)
{
	int	exit_status;

	exit_status = ast_traversal(node->data[0].ast, msvar, 0);
	if ((node->type == NODE_AND && exit_status == EXIT_SUCCESS)
		|| (node->type == NODE_OR && exit_status != EXIT_SUCCESS))
		return (ast_traversal(node->data[1].ast, msvar, 0));
	return (exit_status);
}

int	ast_traversal(t_ast *node, t_msvar *msvar, int pipe_flag)
{
	if (node->type == NODE_CEU)
		return (execute_ceu(node, msvar, pipe_flag));
	if (node->type == NODE_PIPE)
		return (handle_pipe(node, msvar));
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (handle_logic(node, msvar));
	return (EXIT_FAILURE);
}
