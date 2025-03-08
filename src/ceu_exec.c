/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:32:23 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/07 23:15:58 by wchoe            ###   ########.fr       */
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
#define TMP_FILE ".minishell_tmp_file"
#include "builtin.h"

int	process_in_redir(t_in_redir **ir_arr)
{
	int		fd;

	while (*ir_arr)
	{
		if ((*ir_arr)->type == IR_DEFAULT)
		{
			fd = open((*ir_arr)->name, O_RDONLY);
			if (fd < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror((*ir_arr)->name);
				return (FAILURE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if ((*ir_arr)->type == IR_HERE_DOC)
		{
			fd = open((*ir_arr)->name, O_RDONLY);
			if (fd < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror((*ir_arr)->name);
				return (FAILURE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			unlink((*ir_arr)->name);
		}
		else
		{
			// Exception
		}
		++ir_arr;
	}
	return (SUCCESS);
}

int	proces_out_redir(t_out_redir **or_arr)
{
	int	fd;

	while (*or_arr)
	{
		if ((*or_arr)->type == OR_DEFAULT)
			fd = open((*or_arr)->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((*or_arr)->type == OR_APPEND)
			fd = open((*or_arr)->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			// Exception
		}
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror((*or_arr)->name);
			return (FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		++or_arr;
	}
	return (SUCCESS);
}

char	*retrieve_path(char **envp)
{
	while (*envp)
	{
		if (!ft_memcmp(*envp, "PATH=", 5))
			return (*envp + 5);
		++envp;
	}
	return (NULL);
}

void	destory_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	try_command_execve(char **argv, char **envp)
{
	char	**paths;
	t_buf	*buf;
	size_t	i;

	if (*argv[0] == '\0')
	{
		errno = ENOENT;
		return ;
	}
	paths = ft_split(retrieve_path(envp), ':');
	if (!paths)
	{
		// Exception
	}
	buf = create_buf();
	if (!buf)
	{
		// Exception
	}
	i = 0;
	while (paths[i])
	{
		clear_buf(buf);
		cat_buf(buf, paths[i]);
		append_buf(buf, '/');
		cat_buf(buf, argv[0]);
		execve(buf->buffer, argv, envp);
		if (errno && errno != ENOENT)
			break ;
		++i;
	}
	destory_split(paths);
	destroy_buf(buf);
}

#include "ms_signal.h"
#include <sys/wait.h>

int	ceu_exec(t_ceu *ceu, t_msvar *msvar, int flag_pipe_seg)
{
	if (process_in_redir(ceu->ir_arr))
		return (EXIT_FAILURE);
	if (proces_out_redir(ceu->or_arr))
		return (EXIT_FAILURE);
	if (!ceu->argv[0])
		return (EXIT_SUCCESS);
	/*
		We need codes for built-in here
	if (is_buildin(ceu->argv[0]))
		return ();
	*/
	if (flag_pipe_seg)
	{
		clear_ttydup(msvar);
		if (is_builtin(ceu->argv[0]))
		{
			int	exit_status = exec_builtin(ceu->argv, msvar);
			clear_msvar(msvar);
			exit(exit_status);
		}
		clear_ttydup(msvar);
		rollback_sigaction();
		if (ft_strchr(ceu->argv[0], '/'))
			execve(ceu->argv[0], ceu->argv, msvar->envp);
		else
			try_command_execve(ceu->argv, msvar->envp);
		if (ft_strchr(ceu->argv[0], '/') || errno != ENOENT)
			perror(ceu->argv[0]);
		else
		{
			if (!*ceu->argv[0])
				ft_putstr_fd("''", STDERR_FILENO);
			else
				ft_putstr_fd(ceu->argv[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
		clear_msvar(msvar);
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
			exit(127);
		exit(EXIT_FAILURE);
	}
	if (is_builtin(ceu->argv[0]))
		return (exec_builtin(ceu->argv, msvar));
	pid_t	cpid = fork();
	if (cpid < 0)
	{
		perror("minishell: fork");
		return (EXIT_FAILURE);
	}
	if (!cpid)
	{
		clear_ttydup(msvar);
		rollback_sigaction();
		if (ft_strchr(ceu->argv[0], '/'))
			execve(ceu->argv[0], ceu->argv, msvar->envp);
		else
			try_command_execve(ceu->argv, msvar->envp);
		if (ft_strchr(ceu->argv[0], '/') || errno != ENOENT)
			perror(ceu->argv[0]);
		else
		{
			ft_putstr_fd(ceu->argv[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
		clear_msvar(msvar);
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
			exit(127);
		exit(EXIT_FAILURE);
	}
	int	wstatus;
	waitpid(cpid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (WEXITSTATUS(wstatus));
}
