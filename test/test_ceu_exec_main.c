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
		ts = tokenizer(str, &msvar);
		free(str);
		if (!ts)
			continue ;
		msvar.ceu = create_ceu(ts->arr, ts->arr + ts->len);
		destroy_token_stream(ts);
		if (!msvar.ceu)
			continue ;
		msvar.exit_status = ceu_exec(msvar.ceu, &msvar, 0);
		fprintf(stderr, "Command exited with %d\n", msvar.exit_status);
		destroy_ceu(msvar.ceu);
		msvar.ceu = NULL;
		restore_ttydup(&msvar);
	}
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}
