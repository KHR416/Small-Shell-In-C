#include "minishell.h"
#include "token.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	t_token_list	*list;
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
		list = tokenizer_list(str, &msvar);
		free(str);
		if (!list)
			continue ;
		print_token_list(list);
		destroy_token_list(list);
	}
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}
