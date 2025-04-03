/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_analyzer_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/21 17:20:38 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_def.h"
#include "ast_analyzer.h"
#include <stdlib.h>
#include <libft.h>

int	init_ast_analyzer_var(t_ast_analyzer_variables *var)
{
	var->operand_stack = create_stack();
	if (!var->operand_stack)
		return (FAILURE);
	var->operator_stack = create_stack();
	if (!var->operator_stack)
	{
		destroy_stack(var->operand_stack, NULL);
		return (FAILURE);
	}
	ft_memset(&var->ast_node_parenthesis_open, 0, sizeof(t_ast));
	var->ast_node_parenthesis_open.type = NODE_PARANTHESIS_OPEN;
	return (SUCCESS);
}

static void	destroy_ast_wrap(void *root)
{
	destroy_ast(root);
}

static void	destroy_ast_node_wrap(void *node)
{
	if (((t_ast *)node)->type != NODE_PARANTHESIS_OPEN)
		destroy_ast_node(node);
}

void	clear_ast_analyzer_var(t_ast_analyzer_variables *var)
{
	destroy_stack(var->operand_stack, destroy_ast_wrap);
	destroy_stack(var->operator_stack, destroy_ast_node_wrap);
}
