#include <stdio.h>
#include <stdlib.h>
#ifndef MEMCHECK
# include <readline/readline.h>
# include <readline/history.h>
#else
# include <string.h>
#endif
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"
#include "ms_signal.h"
#include "ms_glob.h"

void	print_banner()
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
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("`)", STDERR_FILENO);
}

#define TMP_FILE_TEMPLATE ".tmp_here_doc_file_"

int	set_temp_file_name(t_buf *buf, size_t n)
{
	clear_buf(buf);
	cat_buf(buf, TMP_FILE_TEMPLATE);
	size_t	temp = n;
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

#ifdef MEMCHECK
static char	*readline(const char *prompt)
{
	char	buf[1024];
	printf("%s", prompt);
	if (!fgets(buf, 1024, stdin))
		return (NULL);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';
	return (strdup(buf));
}
#endif

int	process_here_doc_redirec(t_msvar *msvar, char **delimeter)
{
	set_temp_file_name(msvar->buf, msvar->heredoc_count);
	int	fd = open(msvar->buf->buffer, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		char	*str = readline("> ");
		if (!str)
		{
			print_warning_heredoc_eof(*delimeter);
			break ;
		}
		else if (!ft_strcmp(str, *delimeter))
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		free(str);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
	free(*delimeter);
	*delimeter = ft_strdup(msvar->buf->buffer);
	++msvar->heredoc_count;
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

#include <errno.h>

int	remove_temp_files(t_msvar *msvar)
{
	for (size_t i = 0; i < msvar->heredoc_count; ++i)
	{
		set_temp_file_name(msvar->buf, i);
		unlink(msvar->buf->buffer);
	}
	errno = 0;
	return (SUCCESS);
}

void	ms_loop(t_msvar *msvar)
{
	char			*str;
	t_token_stream	*ts;

	while (1)
	{
		ms_signal = 0;
		update_sigaction_interactive();
		clear_buf(msvar->command_buf);
		str = readline(MS_PROMPT);
		if (ms_signal == SIGINT)
			msvar->exit_status = 128 + SIGINT;
		if (!str)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		ts = create_token_stream();
		if (!ts)
			continue ;
		tokenizer_arr_append(ts, str, msvar);
		free(str);
		if (!is_valid(ts, msvar))
		{
			destroy_token_stream(ts);
			#ifndef MEMCHECK
			add_history(msvar->command_buf->buffer);
			#endif
			msvar->exit_status = 2;
			continue ;
		}
		#ifndef MEMCHECK
		add_history(msvar->command_buf->buffer);
		#endif
		process_here_doc(ts, msvar);
		msvar->ast = analyzer(ts);
		destroy_token_stream(ts);
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
	#ifndef MEMCHECK
	rl_clear_history();
	#endif
	ft_putendl_fd("exit", STDERR_FILENO);
	return (msvar.exit_status);
}
