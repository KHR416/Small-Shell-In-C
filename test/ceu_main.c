#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "token.h"
#include "astree.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str = NULL;
	t_token_stream	*ts = NULL;
	t_ceu			*ceu = NULL;

	++argc;
	++argv;
	while (1)
	{
		if (!(str = readline("$ ")))
			break ;
		add_history(str);
		ts = tokenizer(str, envp);
		free(str);
		if (ts->len)
		{
			ceu = create_ceu(ts->arr, ts->arr + ts->len);
			print_ceu(ceu);
			destroy_ceu(ceu);
		}
		destroy_token_stream(ts);
	}
	return (EXIT_SUCCESS);
}