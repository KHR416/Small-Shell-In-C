#include "token.h"
#include <libft.h>
#include <stdlib.h>

t_token_node	*create_token_node(t_token_type type, void *data, void (*del_func)(void *))
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		// Exception
	}
	token->type = type;
	token->data = data;
	token->del_func = del_func;
	t_token_node	*node;
	node = ft_lstnew(token);
	if (!node)
	{
		// Exception
	}
	return (node);
}

void	destroy_token(t_token *token)
{
	if (token->del_func)
		token->del_func(token->data);
	free(token);
}

void	destroy_token_node(t_token_node *node)
{
	destroy_token(node->content);
	free(node);
}

t_token_list	*create_token_list(void)
{
	return (ft_calloc(1, sizeof(t_token_list)));
}

void	destroy_token_list(t_token_list *list)
{
	t_token_node	*it;
	t_token_node	*next;

	it = list->head;
	while (it)
	{
		next = it->next;
		destroy_token_node(it);
		it = next;
	}
	free(list);
}

int		append_token_list(t_token_list *list, t_token_type type, void *data, void (*del_func)(void *))
{
	t_token_node	*new_node;

	new_node = create_token_node(type, data, del_func);
	if (!new_node)
	{
		// Exception
	}
	if (!list->head)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		list->tail = new_node;
	}
	return (SUCCESS);
}


