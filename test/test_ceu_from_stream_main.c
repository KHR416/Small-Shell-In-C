#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"

t_ceu	*create_ceu_from_stream(t_token_stream *stream);

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
		ts = tokenizer_arr(str, &msvar);
		free(str);
		if (!ts->len)
		{
			destroy_token_stream(ts);
			continue ;
		}
		ceu = create_ceu_from_stream(ts);
		destroy_token_stream(ts);
		if (!ceu)
			continue ;
		print_ceu(ceu);
		destroy_ceu(ceu);
	}
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}