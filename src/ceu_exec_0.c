/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_exec_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:32:23 by wchoe             #+#    #+#             */
/*   Updated: 2025/04/01 13:58:14 by chakim           ###   ########.fr       */
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

int	handle_file_open(char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (FAILURE);
	}
	dup2(*fd, STDIN_FILENO);
	close(*fd);
	return (SUCCESS);
}

int	process_in_redir(t_in_redir **ir_arr)
{
	int	fd;
	int	result;

	while (*ir_arr)
	{
		if ((*ir_arr)->type == IR_DEFAULT)
		{
			result = handle_file_open((*ir_arr)->name, &fd);
			if (result == FAILURE)
				return (FAILURE);
		}
		else if ((*ir_arr)->type == IR_HERE_DOC)
		{
			result = handle_file_open((*ir_arr)->name, &fd);
			if (result == FAILURE)
				return (FAILURE);
			unlink((*ir_arr)->name);
		}
		else
			return (FAILURE);
		++ir_arr;
	}
	return (SUCCESS);
}

int	process_out_redir(t_out_redir **or_arr)
{
	int	fd;

	while (*or_arr)
	{
		if ((*or_arr)->type == OR_DEFAULT)
			fd = open((*or_arr)->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((*or_arr)->type == OR_APPEND)
			fd = open((*or_arr)->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			return (FAILURE);
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

void	destroy_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
