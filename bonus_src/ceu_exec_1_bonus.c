/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_exec_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:20:08 by chakim            #+#    #+#             */
/*   Updated: 2025/04/01 13:58:03 by chakim           ###   ########.fr       */
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

char	**prepare_execution_paths(char **envp)
{
	char	*path_env;
	char	**paths;

	path_env = retrieve_path(envp);
	if (!path_env)
	{
		errno = ENOENT;
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (paths);
}

void	try_command_execve(char **argv, char **envp, t_buf *buf)
{
	char	**paths;
	size_t	i;

	if (argv == NULL || argv[0] == NULL || *argv[0] == '\0')
	{
		errno = ENOENT;
		return ;
	}
	paths = prepare_execution_paths(envp);
	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		clear_buf(buf);
		cat_buf(buf, paths[i]);
		append_buf(buf, '/');
		cat_buf(buf, argv[0]);
		execve(buf->buffer, argv, envp);
		if (errno != ENOENT)
			break ;
		i++;
	}
	destroy_split(paths);
}
