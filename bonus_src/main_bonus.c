/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:05:38 by chakim            #+#    #+#             */
/*   Updated: 2025/04/03 21:12:51 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
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
#define TMP_FILE_TEMPLATE ".tmp_here_doc_file_"

static int	process_heredoc_content(int fd, char *delimeter)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
		{
			print_warning_heredoc_eof(delimeter);
			break ;
		}
		if (ft_strcmp(str, delimeter) == 0)
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		free(str);
		ft_putchar_fd('\n', fd);
	}
	return (SUCCESS);
}

int	process_here_doc_redirec(t_msvar *msvar, char **delimeter)
{
	int	fd;

	set_temp_file_name(msvar->buf, msvar->heredoc_count);
	fd = open(msvar->buf->buffer, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	process_heredoc_content(fd, *delimeter);
	close(fd);
	free(*delimeter);
	*delimeter = ft_strdup(msvar->buf->buffer);
	++msvar->heredoc_count;
	return (SUCCESS);
}

static int	process_command(t_msvar *msvar, char *str)
{
	t_token_stream	*ts;

	if (!*str)
	{
		free(str);
		return (FAILURE);
	}
	ts = create_token_stream();
	if (!ts)
		return (FAILURE);
	tokenizer_arr_append(ts, str, msvar);
	free(str);
	if (!validate_and_extend_stream(ts, msvar))
	{
		destroy_token_stream(ts);
		add_history(msvar->command_buf->buffer);
		msvar->exit_status = 2;
		return (FAILURE);
	}
	add_history(msvar->command_buf->buffer);
	process_here_doc(ts, msvar);
	msvar->ast = ast_analyzer(ts);
	destroy_token_stream(ts);
	return (SUCCESS);
}

void	ms_loop(t_msvar *msvar)
{
	char	*str;

	str = NULL;
	while (1)
	{
		g_ms_signal = 0;
		update_sigaction_interactive();
		clear_buf(msvar->command_buf);
		str = readline(MS_PROMPT);
		if (g_ms_signal == SIGINT)
			msvar->exit_status = 128 + SIGINT;
		if (!str)
			break ;
		if (process_command(msvar, str) == FAILURE)
			continue ;
		if (!msvar->ast)
			continue ;
		update_sigaction_control();
		msvar->exit_status = ast_traversal(msvar->ast, msvar, 0);
		restore_ttydup(msvar);
		destroy_ast(msvar->ast);
		remove_temp_files(msvar);
		msvar->heredoc_count = 0;
		msvar->ast = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_msvar	msvar;

	print_banner();
	ms_var_init(argc, argv, envp, &msvar);
	ms_loop(&msvar);
	clear_msvar(&msvar);
	rl_clear_history();
	ft_putendl_fd("exit", STDERR_FILENO);
	return (msvar.exit_status);
}
