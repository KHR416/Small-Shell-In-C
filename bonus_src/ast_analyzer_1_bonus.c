/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_analyzer_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 19:46:22 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_def.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include "ast_analyzer.h"
#include <stdlib.h>
#include <libft.h>

static int	process_operand_token(t_token_stream *stream, t_stack *s)
{
	t_ast	*temp;

	temp = create_ast_node();
	if (!temp)
		return (FAILURE);
	temp->type = NODE_CEU;
	temp->data[0].ceu = create_ceu_from_stream(stream);
	if (!temp->data[0].ceu)
	{
		destroy_ast_node(temp);
		return (FAILURE);
	}
	if (stack_push(s, temp))
	{
		destroy_ast_node(temp);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	handle_operator_precedence(
			t_ast_analyzer_variables *var,
			t_node_type type_to_cmp,
			int (*cmp_func)(t_node_type, t_node_type))
{
	t_ast	*top_operator;
	t_ast	*top_operand;

	while (var->operator_stack->length)
	{
		top_operator = stack_top(var->operator_stack);
		if (cmp_func && cmp_func(top_operator->type, type_to_cmp) < 0)
			break ;
		stack_pop(var->operator_stack, NULL);
		top_operand = stack_top(var->operand_stack);
		stack_pop(var->operand_stack, NULL);
		top_operator->data[1].ast = top_operand;
		top_operand = stack_top(var->operand_stack);
		stack_pop(var->operand_stack, NULL);
		top_operator->data[0].ast = top_operand;
		stack_push(var->operand_stack, top_operator);
	}
}

static int	process_operator_token(
				t_token_stream *stream,
				t_ast_analyzer_variables *var)
{
	t_ast	*operator_node_to_push;
	t_token	*token;

	operator_node_to_push = create_ast_node();
	if (!operator_node_to_push)
		return (FAILURE);
	token = read_token_stream(stream);
	if (token->type == TOKEN_PIPE)
		operator_node_to_push->type = NODE_PIPE;
	else if (token->type == TOKEN_AND_OPERATOR)
		operator_node_to_push->type = NODE_AND;
	else
		operator_node_to_push->type = NODE_OR;
	handle_operator_precedence(var, operator_node_to_push->type, op_cmp);
	if (stack_push(var->operator_stack, operator_node_to_push))
	{
		destroy_ast_node(operator_node_to_push);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	process_parenthesis_token(
			t_token_stream *stream,
			t_ast_analyzer_variables *var)
{
	t_token	*token;

	token = read_token_stream(stream);
	if (!token)
		return (FAILURE);
	if (token->type == TOKEN_PARENTHESIS_OPEN)
	{
		if (stack_push(var->operator_stack, &var->ast_node_parenthesis_open))
			return (FAILURE);
	}
	else
	{
		handle_operator_precedence(var, NODE_PARANTHESIS_OPEN, cmp_not_same);
		stack_pop(var->operator_stack, NULL);
	}
	return (SUCCESS);
}

int	parse_to_ast_analyzer_var(
		t_token_stream *stream,
		t_ast_analyzer_variables *var)
{
	if (!peek_token_stream(stream, 0))
		return (FAILURE);
	while (peek_token_stream(stream, 0) != TOKEN_NONE)
	{
		if (is_ceu_token(peek_token_stream(stream, 0)->type))
		{
			if (process_operand_token(stream, var->operand_stack))
				return (FAILURE);
		}
		else if (is_operator_token(peek_token_stream(stream, 0)->type))
		{
			if (process_operator_token(stream, var))
				return (FAILURE);
		}
		else
		{
			if (process_parenthesis_token(stream, var))
				return (FAILURE);
		}
	}
	handle_operator_precedence(var, NODE_NONE, NULL);
	return (SUCCESS);
}
