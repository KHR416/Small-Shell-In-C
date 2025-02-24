#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"
#define GOD_ASCII	"God"

char	*rl_gets(void);

void	print_god()
{
	char	buf[BUFFER_SIZE];
	int		fd;
	ssize_t	bytes;

	fd = open(GOD_ASCII, O_RDONLY);
	while (1)
	{
		bytes = read(fd, buf, BUFFER_SIZE - 1);
		if (bytes <= 0)
			break ;
		buf[bytes] = '\0';
		ft_putstr_fd(buf, STDOUT_FILENO);
	}
	close(fd);
}

int	main(int argc, char **argv, char **envp)
{
	char			*str = NULL;
	t_token_stream	*ts = NULL;
	t_ast			*ast = NULL;
	t_msvar			msvar;

	print_god();
	ms_var_init(argc, argv, envp, &msvar);
	while (1)
	{
		str = rl_gets();
		if (!str)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		ts = tokenizer(str, &msvar);
		free(str);
		if (ts == NULL)
			continue ;
		if (!ts->len)
		{
			destroy_token_stream(ts);
			continue ;
		}
		ast = analyzer(ts);
		destroy_token_stream(ts);
		if (!ast)
			continue ;
		ast_traversal(ast, ast, &msvar);
		destroy_ast(ast);
	}
	free_msvar(&msvar);
	return (EXIT_SUCCESS);
}
