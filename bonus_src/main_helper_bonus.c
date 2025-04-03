/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:29:38 by chakim            #+#    #+#             */
/*   Updated: 2025/04/03 21:13:08 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"
#include "ms_signal.h"
#include "ms_glob.h"
#include <errno.h>
#include "helpers.h"
#include <readline/readline.h>
#include <readline/history.h>
#define TMP_FILE_TEMPLATE ".tmp_here_doc_file_"

void	print_banner(void)
{
	char	buf[BUFFER_SIZE];
	int		fd;
	ssize_t	bytes;

	fd = open(".banner", O_RDONLY);
	if (fd < 0)
		return ;
	while (1)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		write(STDOUT_FILENO, buf, bytes);
	}
	close(fd);
}

void	print_warning_heredoc_eof(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("`)", STDERR_FILENO);
}

int	set_temp_file_name(t_buf *buf, size_t n)
{
	size_t	temp;

	clear_buf(buf);
	cat_buf(buf, TMP_FILE_TEMPLATE);
	temp = n;
	while (1)
	{
		temp = n / 10;
		if (!temp)
			break ;
		append_buf(buf, n / temp + '0');
		n -= 10 * temp;
	}
	append_buf(buf, n + '0');
	return (SUCCESS);
}

int	remove_temp_files(t_msvar *msvar)
{
	size_t	i;

	i = 0;
	while (i < msvar->heredoc_count)
	{
		set_temp_file_name(msvar->buf, i);
		unlink(msvar->buf->buffer);
		++i;
	}
	errno = 0;
	return (SUCCESS);
}

int	process_here_doc(t_token_stream *stream, t_msvar *msvar)
{
	while (stream->arr[stream->offset].type != TOKEN_NONE)
	{
		if (stream->arr[stream->offset].type == TOKEN_HERE_DOC)
		{
			++stream->offset;
			process_here_doc_redirec(msvar, &stream->arr[stream->offset].data);
		}
		++stream->offset;
	}
	stream->offset = 0;
	return (SUCCESS);
}
