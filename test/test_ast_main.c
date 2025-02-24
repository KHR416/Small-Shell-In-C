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
	#ifndef MEMCHECK
	char			*str = NULL;
	#else
	char			buf[BUFFER_SIZE];
	#endif	// MEMCHECK
	t_token_stream	*ts = NULL;
	t_ast			*ast = NULL;
	t_msvar			msvar;

	ms_var_init(argc, argv, envp, &msvar);
	while (1)
	{
		#ifndef MEMCHECK
		if (!(str = readline("$ ")))
			break ;
		add_history(str);
		ts = tokenizer(str, &msvar);
		free(str);
		#else
		printf("$ ");
		if (!fgets(buf, BUFFER_SIZE, stdin))
			break ;
		buf[strlen(buf) - 1] = '\0';
		ts = tokenizer(buf, &msvar);
		#endif	//MEMCHECK
		if (ts == NULL)
			continue ;
		if (ts->len && (ast = analyzer(ts)))
		{
			destroy_token_stream(ts);
			ast_traversal(ast, ast, &msvar);
			destroy_ast(ast);
		}
		else
			destroy_token_stream(ts);
	}
	free_msvar(&msvar);
	return (EXIT_SUCCESS);
}
