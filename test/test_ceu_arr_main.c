#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"
#include "generic_array.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str = NULL;
	t_token_stream	*ts = NULL;
	t_msvar			msvar;
	t_ceu			**ceu_arr;

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
		ceu_arr = create_ceu_arr(ts);
		destroy_token_stream(ts);
		if (!ceu_arr)
			continue ;
		print_ceu_arr(ceu_arr);
		destroy_void_arr((void **)ceu_arr, destroy_ceu);
	}
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}