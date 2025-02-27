#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str = NULL;
	t_token_stream	*ts = NULL;
	t_ceu			*ceu = NULL;
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
		ts = tokenizer(str, &msvar);
		free(str);
		if (ts->len)
		{
			ceu = create_ceu(ts->arr, ts->arr + ts->len);
			print_ceu(ceu);
			destroy_ceu(ceu);
		}
		destroy_token_stream(ts);
	}
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}