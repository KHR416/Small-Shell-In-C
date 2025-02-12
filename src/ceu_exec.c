/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:32:23 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/10 18:34:26 by wchoe            ###   ########.fr       */
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

void	print_warning_heredoc_eof(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("`)", STDERR_FILENO);
}

int	process_in_redir(t_list *ir_list)
{
	int		fd;
	char	*str;

	while (ir_list)
	{
		if (((t_in_redir *)ir_list->content)->type == IR_DEFAULT)
		{
			fd = open(((t_in_redir *)ir_list->content)->name, O_RDONLY);
			if (fd < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(((t_in_redir *)ir_list->content)->name);
				return (FAILURE);
			}
			if (!ir_list->next)
				dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (((t_in_redir *)ir_list->content)->type == IR_HERE_DOC)
		{
			fd = open(TMP_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			while (1)
			{
				str = readline("> ");
				if (!str)
				{
					print_warning_heredoc_eof(((t_in_redir *)ir_list->content)->name);
					break ;
				}
				else if (!ft_memcmp(str, ((t_in_redir *)ir_list->content)->name, ft_strlen(((t_in_redir *)ir_list->content)->name)))
				{
					free(str);
					break ;
				}
				write(fd, str, ft_strlen(str));
				free(str);
				ft_putchar_fd('\n', fd);
			}
			close(fd);
			fd = open(TMP_FILE, O_RDONLY);
			unlink(TMP_FILE);
			if (!ir_list->next)
				dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
		{
			// Exception
		}
		ir_list = ir_list->next;
	}
	return (SUCCESS);
}

int	proces_out_redir(t_list *or_list)
{
	int	fd;

	while (or_list)
	{
		if (((t_out_redir *)or_list->content)->type == OR_DEFAULT)
			fd = open(((t_out_redir *)or_list->content)->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (((t_out_redir *)or_list->content)->type == OR_APPEND)
			fd = open(((t_out_redir *)or_list->content)->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			// Exception
		}
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(((t_out_redir *)or_list->content)->name);
			return (FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		or_list = or_list->next;
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

void	try_execve_with_path(char **argv, char **envp)
{
	char	**paths;
	t_buf	*buf;
	size_t	i;

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
		if (errno == EACCES)
			break ;
		++i;
	}
	destory_split(paths);
	destroy_buf(buf);
}

void	ceu_exec(t_ceu *ceu, t_msvar *msvar)
{
	if (process_in_redir(ceu->ir_list))
	{
		destroy_ceu(ceu);
		free_msvar(msvar);
		exit(EXIT_FAILURE);
	}
	if (proces_out_redir(ceu->or_list))
	{
		destroy_ceu(ceu);
		free_msvar(msvar);
		exit(EXIT_FAILURE);
	}
	if (!ceu->argv[0])
		exit(EXIT_SUCCESS);
	try_execve_with_path(ceu->argv, msvar->envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(ceu->argv[0]);
	destroy_ceu(ceu);
	free_msvar(msvar);
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(EXIT_FAILURE);
}
