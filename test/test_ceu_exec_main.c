#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"

void	ceu_exec(t_ceu *ceu, t_msvar *msvar);

int	main(int argc, char **argv, char **envp)
{
	char			*str = NULL;
	t_token_stream	*ts = NULL;
	t_ceu			*ceu = NULL;
	t_msvar			msvar;
	pid_t			cpid;
	int				wstatus;

	ms_var_init(argc, argv, envp, &msvar);
	while (1)
	{
		if (!(str = readline("$ ")))
			break ;
		add_history(str);
		ts = tokenizer(str, &msvar);
		free(str);
		if (ts->len && (ceu = create_ceu(ts->arr, ts->arr + ts->len)))
		{
			cpid = fork();
			if (!cpid)
				ceu_exec(ceu, &msvar);
			else
			{
				waitpid(cpid, &wstatus, 0);
				printf("The child process is terminated with exit code: %d\n", WEXITSTATUS(wstatus));
			}
			destroy_ceu(ceu);
		}
		destroy_token_stream(ts);
	}
	free_msvar(&msvar);
	return (EXIT_SUCCESS);
}
