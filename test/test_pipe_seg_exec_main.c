#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"

void	pipe_seg_exec(t_pipe_seg *ps, t_msvar *msvar);

int	main(int argc, char **argv, char **envp)
{
	char			*str = NULL;
	t_token_stream	*ts = NULL;
	t_pipe_seg		*ps = NULL;
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
		if (ts->len && (ps = create_pipe_seg(ts->arr, ts->arr + ts->len)))
		{
			cpid = fork();
			if (!cpid)
				pipe_seg_exec(ps, &msvar);
			else
			{
				waitpid(cpid, &wstatus, 0);
				printf("The child process is terminated with exit code: %d\n", WEXITSTATUS(wstatus));
			}
			destroy_pipe_seg(ps);
		}
		destroy_token_stream(ts);
	}
	free_msvar(&msvar);
	return (EXIT_SUCCESS);
}