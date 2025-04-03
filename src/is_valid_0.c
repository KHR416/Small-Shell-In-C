/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:13:31 by chakim            #+#    #+#             */
/*   Updated: 2025/03/25 19:08:16 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "token.h"

static int	check_parenthesis(t_token_stream *ts, size_t *p_count)
{
	if (ts->arr[ts->offset].type == TOKEN_PARENTHESIS_OPEN)
	{
		if (ts->offset && ts->arr[ts->offset - 1].type == TOKEN_LITERAL)
		{
			print_error_unexpected_token(ts->arr[ts->offset].type);
			return (FALSE);
		}
		++(*p_count);
		++ts->offset;
		return (TRUE);
	}
	if (!ts->offset || ts->arr[ts->offset - 1].type != TOKEN_LITERAL \
		|| !(*p_count))
	{
		print_error_unexpected_token(ts->arr[ts->offset].type);
		return (FALSE);
	}
	--(*p_count);
	++ts->offset;
	return (TRUE);
}

static int	check_literal_and_redirect(t_token_stream *ts)
{
	if (ts->arr[ts->offset].type == TOKEN_LITERAL)
	{
		++ts->offset;
		return (TRUE);
	}
	if (is_redirect_token(ts->arr[ts->offset].type))
	{
		++ts->offset;
		if (ts->arr[ts->offset].type != TOKEN_LITERAL)
		{
			print_error_unexpected_token(ts->arr[ts->offset].type);
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	check_operator(t_token_stream *ts, t_msvar *msvar)
{
	if (is_operator_token(ts->arr[ts->offset].type))
	{
		if (!ts->offset || (ts->arr[ts->offset - 1].type != TOKEN_LITERAL \
			&& ts->arr[ts->offset - 1].type != TOKEN_PARENTHESIS_CLOSE))
		{
			print_error_unexpected_token(ts->arr[ts->offset].type);
			return (FALSE);
		}
		++ts->offset;
		if (ts->arr[ts->offset].type == TOKEN_NONE \
			&& read_line_and_extend_stream(ts, msvar))
		{
			ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
			ft_putendl_fd("unexpected end of file", STDERR_FILENO);
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	check_end_of_stream(t_token_stream *ts, size_t p_count, \
	t_msvar *msvar)
{
	if (ts->arr[ts->offset].type == TOKEN_NONE && p_count \
		&& read_line_and_extend_stream(ts, msvar))
	{
		ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
		ft_putendl_fd("unexpected end of file", STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}

int	validate_and_extend_stream(t_token_stream *ts, t_msvar *msvar)
{
	size_t	p_count;

	p_count = 0;
	while (ts->arr[ts->offset].type != TOKEN_NONE)
	{
		if (!check_literal_and_redirect(ts))
			return (FALSE);
		if (!check_operator(ts, msvar))
			return (FALSE);
		if (ts->arr[ts->offset].type == TOKEN_PARENTHESIS_OPEN \
			|| ts->arr[ts->offset].type == TOKEN_PARENTHESIS_CLOSE)
		{
			if (!check_parenthesis(ts, &p_count))
				return (FALSE);
		}
		if (!check_end_of_stream(ts, p_count, msvar))
			return (FALSE);
	}
	ts->offset = 0;
	return (TRUE);
}
