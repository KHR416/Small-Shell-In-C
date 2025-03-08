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

int	next_name_buf(t_buf *buf)
{
	size_t	i = buf->length - 1;
	while (1)
	{
		if (ft_isdigit(buf->buffer[i]))
		{
			if ('0' <= buf->buffer[i] && buf->buffer[i] < '9')
			{
				++buf->buffer[i];
				return (SUCCESS);
			}
			else
			{
				buf->buffer[i] = '0';
				--i;
			}
		}
		else
		{
			++i;
			buf->buffer[i] = '1';
			return (append_buf(buf, '0'));
		}
	}
}
#ifdef MEMCHECK
char	*readline(const char *prompt)
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

int	process_here_doc_redirection(t_buf *buf, t_in_redir **ir_it)
{
	while (*ir_it)
	{
		if ((*ir_it)->type == IR_DEFAULT)
			++ir_it;
		else if ((*ir_it)->type == IR_HERE_DOC)
		{
			int	fd = open(buf->buffer, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			while (1)
			{
				char	*str = readline("> ");
				if (!str)
				{
					print_warning_heredoc_eof((*ir_it)->name);
					break ;
				}
				else if (!ft_memcmp(str, (*ir_it)->name, ft_strlen((*ir_it)->name)))
				{
					free(str);
					break ;
				}
				write(fd, str, ft_strlen(str));
				free(str);
				ft_putchar_fd('\n', fd);
			}
			close(fd);
			free((*ir_it)->name);
			(*ir_it)->name = strdup(buf->buffer);
			if (!(*ir_it)->name)
			{
				// Exception!
			}
			if (next_name_buf(buf))
			{
				// Exception!
			}
			++ir_it;
		}
		else
		{
			// Exception!
		}
	}
	return (SUCCESS);
}

int	process_here_doc_recursive(t_ast *node, t_buf *buf)
{
	if (node->type == NODE_CEU)
	{
		process_here_doc_redirection(buf, node->data->ceu->ir_arr);
		return (SUCCESS);
	}
	else if (node->type == NODE_PIPE_SEG) // or CEU
	{
		t_list	*pipe_it = node->data->pipe_seg->ceu_list;
		while (pipe_it)
		{
			process_here_doc_redirection(buf, ((t_ceu *)(pipe_it->content))->ir_arr);
			pipe_it = pipe_it->next;
		}
		return (SUCCESS);
	}
	// else if (node->type == NODE_LOGIC) <- Post-order DFS
	// else <- Exception!
	return (SUCCESS);
}

int	process_here_doc(t_ast *ast)
{
	t_buf	*buf;

	buf = create_buf();
	cat_buf(buf, ".tmp_here_doc_file_0");
	process_here_doc_recursive(ast, buf);
	destroy_buf(buf);
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
		str = rl_gets();
		if (ms_signal == SIGINT)
			msvar->exit_status = 128 + SIGINT;
		if (!str)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		ts = tokenizer_arr(str, msvar);
		free(str);
		if (!ts)
			continue ;
		msvar->ast = analyzer(ts);
		destroy_token_stream(ts);
		if (!msvar->ast)
			continue ;
		process_here_doc(msvar->ast);
		update_sigaction_control();
		msvar->exit_status = ast_traversal(msvar->ast, msvar);
		destroy_ast(msvar->ast);
		msvar->ast = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_msvar				msvar;

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
