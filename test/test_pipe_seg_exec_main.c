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
	t_pipe_seg		*ps = NULL;
	t_msvar			msvar;
	pid_t			cpid;
	int				wstatus = 255;

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
		if (ts->len && (ps = create_pipe_seg(ts->arr, ts->arr + ts->len)))
		{
			destroy_token_stream(ts);
			cpid = fork();
			if (cpid == -1)
				perror("fork");
			else if (cpid == 0)
			{
				int exit_status = pipe_seg_exec(ps, &msvar);
				destroy_pipe_seg(ps);
				free_msvar(&msvar);
				exit(exit_status);
			}
			else
			{
				waitpid(cpid, &wstatus, 0);
				fprintf(stderr, "The child process is terminated with exit code: %d\n", WEXITSTATUS(wstatus));
			}
			destroy_pipe_seg(ps);
		}
		else
			destroy_token_stream(ts);
	}
	free_msvar(&msvar);
	return (EXIT_SUCCESS);
}
