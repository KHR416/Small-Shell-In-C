/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:23:52 by chakim            #+#    #+#             */
/*   Updated: 2025/03/25 16:42:10 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "minishell.h"

void	destroy_stack(t_stack *s, void (del_func)(void *))
{
	size_t	i;

	i = 0;
	if (del_func)
		while (i < s->length)
			del_func(s->data[i++]);
	free(s->data);
	free(s);
}

int	is_empty_stack(t_stack *s)
{
	if (s->length == 0)
		return (1);
	return (0);
}

int	stack_push(t_stack *s, void *entry)
{
	if (s->length + 1 > s->capacity)
		if (realloc_gen_arr(s, s->capacity << 1))
			return (FAILURE);
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
