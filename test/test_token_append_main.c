#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "token.h"
#include "astree.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	t_token_stream	*ts = create_token_stream();
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
		tokenizer_arr_append(ts, str, &msvar);
		free(str);
		while (ts->arr[ts->len - 1].type == TOKEN_PIPE || ts->arr[ts->len - 1].type == TOKEN_AND_OPERATOR || ts->arr[ts->len - 1].type == TOKEN_OR_OPERATOR)
			read_and_append(ts, &msvar);
		print_token_stream(ts);
	}
	destroy_token_stream(ts);
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}