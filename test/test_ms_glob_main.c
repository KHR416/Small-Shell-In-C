#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char	*str;
	char	**glob;

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
		glob = ms_glob(str);
		free(str);
		if (!glob)
			continue ;
		for (size_t i = 0; glob[i]; ++i)
			printf("%s\n", glob[i]);
		for (size_t i = 0; glob[i]; ++i)
			free(glob[i]);
		free(glob);
	}
	return (EXIT_SUCCESS);
}
