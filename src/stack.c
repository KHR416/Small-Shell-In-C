#include "stack.h"
#include "minishell.h"

t_stack	*create_stack(void)
{
	return (create_gen_arr());
}

void	destroy_stack(t_stack *s, void (del_func)(void *))
{
	destroy_gen_arr(s, del_func);
}

int	is_empty_stack(t_stack *s)
{
	if (s->length == 0)
		return (1);
	return (0);
}

int	stack_push(t_stack *s, void *entry, void *(*dup_func)(void *))
{
	if (s->length + 1 > s->capacity)
		if (realloc_gen_arr(s, s->capacity << 1))
			return (FAILURE);
	if (dup_func)
	{
		s->data[s->length] = dup_func(entry);
		if (!s->data[s->length])
			return (FAILURE);
	}
	else
		s->data[s->length] = entry;
	++s->length;
	return (SUCCESS);
}

void	*stack_top(t_stack *s)
{
	if (is_empty_stack(s))
		return (NULL);
	return (s->data[s->length - 1]);
}

int	stack_pop(t_stack *s, void (*destroy_func)(void *))
{
	if (is_empty_stack(s))
		return (FAILURE);
	if (destroy_func)
		destroy_func(stack_top(s));
	--s->length;
	return (SUCCESS);
}