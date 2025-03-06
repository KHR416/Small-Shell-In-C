#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "token.h"
#include "astree.h"

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
		list = tokenizer_test(str, &msvar);
		free(str);
		print_token_list(list);
		destroy_token_list(list);
	}
	clear_msvar(&msvar);
	return (EXIT_SUCCESS);
}