#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "token.h"
#include "astree.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	t_token_stream	*ts;
	t_pipe_seg		*ps;
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
		if (ts->len)
		{
			ps = create_pipe_seg(ts->arr, ts->arr + ts->len);
			print_pipe_seg(ps);
			destroy_pipe_seg(ps);
		}
		destroy_token_stream(ts);
	}
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}