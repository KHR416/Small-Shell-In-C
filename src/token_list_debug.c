#ifdef DEBUG
# include <libft.h>
# include <stdio.h>
# include "token.h"

void	print_token_list(t_token_list *list)
{
	t_token_node	*it = list->head;
	while (it)
	{
		print_token(it->content);
		it = it->next;
	}
}
#endif	// DEBUG