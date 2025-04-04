/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_exec_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:20:08 by chakim            #+#    #+#             */
/*   Updated: 2025/04/04 20:13:44 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ceu.h"
#include "minishell.h"
#include <stdlib.h>
#include <libft.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <libft.h>
#include <errno.h>
#include "builtin.h"
#include "ms_signal.h"
#include <sys/wait.h>
#define TMP_FILE ".minishell_tmp_file"

static void	handle_command_error(char *cmd)
{
	if (ft_strchr(cmd, '/') || errno != ENOENT)
		perror(cmd);
	else
	{
		if (!*cmd)
			ft_putstr_fd("''", STDERR_FILENO);
		else
			ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
}

static void	execute_command_on_child_and_exit(t_ceu *ceu, t_msvar *msvar)
{
	clear_ttydup(msvar);
	if (ft_strchr(ceu->argv[0], '/'))
		execve(ceu->argv[0], ceu->argv, msvar->envp);
	else
		try_command_execve(ceu->argv, msvar->envp, msvar->buf);
	handle_command_error(ceu->argv[0]);
	clear_msvar(msvar);
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(EXIT_FAILURE);
}

static void	execute_in_pipe(t_ceu *ceu, t_msvar *msvar)
{
	int	exit_status;

	clear_ttydup(msvar);
	if (is_builtin(ceu->argv[0]))
	{
		exit_status = exec_builtin(ceu->argv, msvar);
		clear_msvar(msvar);
		exit(exit_status);
	}
	execute_command_on_child_and_exit(ceu, msvar);
}

static int	execute_normal(t_ceu *ceu, t_msvar *msvar)
{
	pid_t	cpid;
	int		wstatus;

	if (is_builtin(ceu->argv[0]))
		return (exec_builtin(ceu->argv, msvar));
	cpid = fork();
	if (cpid < 0)
	{
		perror("minishell: fork");
		return (EXIT_FAILURE);
	}
	if (!cpid)
		execute_command_on_child_and_exit(ceu, msvar);
	waitpid(cpid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (WEXITSTATUS(wstatus));
}

// If flag_pipe_seg is not true, it doesn not return anything but exit with the
// exit status.
int	ceu_exec(t_ceu *ceu, t_msvar *msvar, int flag_pipe_seg)
{
	if (process_in_redir(ceu->ir_arr))
		return (EXIT_FAILURE);
	if (process_out_redir(ceu->or_arr))
		return (EXIT_FAILURE);
	if (!ceu->argv[0])
		return (EXIT_SUCCESS);
	if (flag_pipe_seg)
		execute_in_pipe(ceu, msvar);
	return (execute_normal(ceu, msvar));
}
