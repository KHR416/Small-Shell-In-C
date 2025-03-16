#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str = NULL;
	t_token_stream	*ts = NULL;
	t_msvar			msvar;

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
		ts = tokenizer_arr(str, &msvar);
		free(str);
		if (!ts)
			continue ;
		if (!is_valid(ts, &msvar))
		{
			destroy_token_stream(ts);
			continue ;
		}
		ts->offset = 0;
		msvar.ast = analyzer(ts);
		destroy_token_stream(ts);
		if (!msvar.ast)
			continue ;
		msvar.exit_status = ast_traversal(msvar.ast, &msvar, 0);
		restore_ttydup(&msvar);
		fprintf(stderr, "AST exited with %d\n", msvar.exit_status);
		destroy_ast(msvar.ast);
		msvar.ast = NULL;
	}
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}
