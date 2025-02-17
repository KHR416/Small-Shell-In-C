/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/17 17:53:58 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

size_t	pipe_seg_len(t_token *iter_begin, t_token *iter_end)
{
	size_t	count;

	count = 0;
	while (iter_begin < iter_end)
	{
		if (iter_begin->type == TOKEN_PIPE)
			++count;
		++iter_begin;
	}
	return (count);
}

void	destroy_pipe_seg(t_pipe_seg *ps)
{
	ft_lstclear(&ps->ceu_list, destroy_ceu);
	free(ps);
}

// int	is_valid_pipe_seg_ta(t_token *ta, size_t begin, size_t end)
// {
	
// }

// It returns the pipe closest to `iter_begin`.
// If the pipe doesn't exist, it returns `iter_end`.
t_token	*find_pipe(t_token *iter_begin, t_token *iter_end)
{
	while (iter_begin < iter_end)
	{
		if (iter_begin->type == TOKEN_PIPE)
			return (iter_begin);
		++iter_begin;
	}
	return (iter_begin);
}

t_token	*next_pipe_arg(t_list *arg_pipe, t_token *end)
{
	if (!arg_pipe || !arg_pipe->next)
		return (end);
	return (arg_pipe->next->content);
}

int	is_ceu_token(t_token_type type)
{
	if (TOKEN_LITERAL <= type && type <= TOKEN_APPEND_REDIRECT)
		return (1);
	return (0);
}

size_t	ceu_token_len(t_token *iter_begin, t_token *iter_end)
{
	size_t	len;

	len = 0;
	while (iter_begin < iter_end)
	{
		if (!is_ceu_token(iter_begin->type))
			return (len);
		++len;
		++iter_begin;
	}
	return (len);
}

t_pipe_seg	*create_pipe_seg(t_token *iter_begin, t_token *iter_end)
{
	t_pipe_seg	*ps;
	void		*temp;

	if (iter_begin == iter_end)
	{
		print_error_unexpected_token(iter_begin->type);
		return (NULL);
	}
	ps = ft_calloc(1, sizeof(t_pipe_seg));
	if (!ps)
		return (NULL);
	while (iter_begin < iter_end)
	{
		temp = create_ceu(iter_begin, iter_begin + ceu_token_len(iter_begin, iter_end));
		if (!temp || ft_lstpush_back(&ps->ceu_list, temp))
		{
			destroy_pipe_seg(ps);
			return (NULL);
		}
		iter_begin += ceu_token_len(iter_begin, iter_end);
		if (iter_begin < iter_end && !is_ceu_token((++iter_begin)->type))
		{
			// We need to discuss about the behavior of this function on this case.
			// Should this function take new line like bash?
			print_error_unexpected_token(iter_begin->type);
			destroy_pipe_seg(ps);
			return (NULL);
		}
	}
	return (ps);
}

int	print_pipe_seg(t_pipe_seg *ps)
{
	#ifdef DEBUG
	if (!ps || !ps->ceu_list)
		return (FAILURE);
	for (t_list *it = ps->ceu_list; it; it = it->next)
	{
		if (it != ps->ceu_list)
			fprintf(stderr, "====PIPE====\n");
		if (print_ceu(it->content))
			return (FAILURE);
	}
	return (SUCCESS);
	#endif
}
