/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/15 21:38:55 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>
#include "generic_array.h"

t_ast	*create_ast_node(void)
{
	return (ft_calloc(1, sizeof(t_ast)));
}

void	destroy_pipe_seg_wrap(void *ps);

void	destroy_ast_node(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CEU)
		destroy_ceu(node->data[0].ceu);
	// It deletes ceu, but doesn't do for another AST.
	// Because ceu is inferior to an AST, an AST isn't inferior to other AST.
	free(node);
}

int is_operator_node(t_node_type type)
{
	return (type == NODE_PIPE || type == NODE_AND || type == NODE_OR);
}

int is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND_OPERATOR || type == TOKEN_OR_OPERATOR);
}

void	destroy_ast(t_ast *root)
{
	if (!root)
		return ;
	if (is_operator_node(root->type))
	{
		destroy_ast(root->data[0].ast);
		destroy_ast(root->data[1].ast);
	}
	destroy_ast_node(root);
}

int	is_token_test(t_token_type type)
{
	return (is_ceu(type) || type == TOKEN_PIPE || type == TOKEN_AND_OPERATOR || type == TOKEN_OR_OPERATOR);
}

#include "stack.h"

int	op_cmp(t_node_type type1, t_node_type type2)
{
	if (type1 == type2)
		return (0);
	if (type1 == NODE_PIPE && (type2 == NODE_AND || type2 == NODE_OR))
		return (1);
	return (-1);
}

t_ast	*analyzer(t_token_stream *ts)
{
	// Priority : Higher <- '(, )' / '>, >>, <, <<, command' / '|' / '&&, ||' -> Lower
	t_stack	*s_operand = create_stack();
	t_stack	*s_operator = create_stack();
	t_ast	*temp_ast;
	t_ast	ast_parenthesis_open;

	ast_parenthesis_open.type = NODE_PARANTHESIS_OPEN;
	while (ts->arr[ts->offset].type != TOKEN_NONE)
	{
		if (is_ceu(ts->arr[ts->offset].type))
		{
			temp_ast = create_ast_node();
			if (!temp_ast)
			{
				// Exception
			}
			temp_ast->type = NODE_CEU;
			temp_ast->data[0].ceu = create_ceu_from_stream(ts);
			if (!temp_ast->data[0].ceu)
			{
				// Exception
			}
			stack_push(s_operand, temp_ast, NULL);
		}
		else if (is_operator_token(ts->arr[ts->offset].type))
		{
			temp_ast = create_ast_node();
			if (!temp_ast)
			{
				// Exception
			}
			if (ts->arr[ts->offset].type == TOKEN_PIPE)
				temp_ast->type = NODE_PIPE;
			else if (ts->arr[ts->offset].type == TOKEN_AND_OPERATOR)
				temp_ast->type = NODE_AND;
			else
				temp_ast->type = NODE_OR;
			t_ast	*top_operator, *top_operand;
			while (s_operator->length)
			{
				top_operator = stack_top(s_operator);
				if (op_cmp(top_operator->type, temp_ast->type) < 0)
					break ;
				stack_pop(s_operator, NULL);

				top_operand = stack_top(s_operand);
				stack_pop(s_operand, NULL);
				top_operator->data[1].ast = top_operand;

				top_operand = stack_top(s_operand);
				stack_pop(s_operand, NULL);
				top_operator->data[0].ast = top_operand;

				stack_push(s_operand, top_operator, NULL);
			}
			stack_push(s_operator, temp_ast, NULL);
			++ts->offset;
		}
		else
		{
			if (ts->arr[ts->offset].type == TOKEN_PARENTHESIS_OPEN)
			{
				stack_push(s_operator, &ast_parenthesis_open, NULL);
				++ts->offset;
			}
			else
			{
				t_ast	*top_operator, *top_operand;
				while (1)
				{
					top_operator = stack_top(s_operator);
					if (top_operator->type == NODE_PARANTHESIS_OPEN)
					{
						stack_pop(s_operator, NULL);
						break ;
					}
					stack_pop(s_operator, NULL);

					top_operand = stack_top(s_operand);
					stack_pop(s_operand, NULL);
					top_operator->data[1].ast = top_operand;

					top_operand = stack_top(s_operand);
					stack_pop(s_operand, NULL);
					top_operator->data[0].ast = top_operand;

					stack_push(s_operand, top_operator, NULL);
				}
				++ts->offset;
			}
		}
	}
	t_ast	*top_operator, *top_operand;
	while (s_operator->length)
	{
		top_operator = stack_top(s_operator);
		stack_pop(s_operator, NULL);

		top_operand = stack_top(s_operand);
		stack_pop(s_operand, NULL);
		top_operator->data[1].ast = top_operand;

		top_operand = stack_top(s_operand);
		stack_pop(s_operand, NULL);
		top_operator->data[0].ast = top_operand;

		stack_push(s_operand, top_operator, NULL);
	}
	destroy_stack(s_operator, NULL);
	temp_ast = stack_top(s_operand );
	stack_pop(s_operand, NULL);
	destroy_stack(s_operand, NULL);
	return (temp_ast);
}

#include <sys/wait.h>
int	ast_traversal(t_ast *node, t_msvar *msvar, int pipe_flag)
{
	if (node->type == NODE_CEU)
		return (ceu_exec(node->data[0].ceu, msvar, pipe_flag));
	if (node->type == NODE_PIPE)
	{
		int	pipefd[2];
		if (pipe(pipefd) < 0)
		{
			// Exception
		}
		pid_t	cpid_left = fork();
		if (cpid_left < 0)
		{
			// Exception
		}
		if (!cpid_left)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			int exit_status = ast_traversal(node->data[0].ast, msvar, 1);
			clear_msvar(msvar);
			exit(exit_status);
		}
		
		pid_t	cpid_right = fork();
		if (cpid_right < 0)
		{
			// Exception
		}
		if (!cpid_right)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			int exit_status = ast_traversal(node->data[1].ast, msvar, 1);
			clear_msvar(msvar);
			exit(exit_status);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		int	wstatus;
		waitpid(cpid_left, NULL, 0);
		waitpid(cpid_right, &wstatus, 0);
		if (WIFSIGNALED(wstatus))
			return (128 + WTERMSIG(wstatus));
		return (WEXITSTATUS(wstatus));
	}
	else if (node->type == NODE_AND || node->type == NODE_OR)
	{
		int	exit_status = ast_traversal(node->data[0].ast, msvar, 0);
		if ((node->type == NODE_AND && exit_status == EXIT_SUCCESS) || (node->type == NODE_OR && exit_status != EXIT_SUCCESS))
			return (ast_traversal(node->data[1].ast, msvar, 0));
		// TODO:
		// Delete temp file for right ast node.
		return (exit_status);
	}
	else
	{
		// Exception
		return (EXIT_FAILURE);
	}
}
