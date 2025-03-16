#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"
#include "generic_array.h"

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
		msvar.ceu_arr = (void **)create_ceu_arr(ts, &msvar);
		destroy_token_stream(ts);
		if (!msvar.ceu_arr)
			continue ;
		msvar.exit_status = ceu_arr_exec((t_ceu **)msvar.ceu_arr, &msvar);
		destroy_void_arr(msvar.ceu_arr, destroy_ceu);
		msvar.ceu_arr = NULL;
		fprintf(stderr, "ceu arr exited with %d\n", msvar.exit_status);
	}
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}
