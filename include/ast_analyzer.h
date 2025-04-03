/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_analyzer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:14:15 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 19:45:27 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_ANALYZER_H
# define AST_ANALYZER_H
# include "stack.h"
# include "astree.h"

typedef struct s_ast_analyzer_variables
{
	t_stack	*operand_stack;
	t_stack	*operator_stack;
	t_ast	ast_node_parenthesis_open;
}	t_ast_analyzer_variables;

int		init_ast_analyzer_var(t_ast_analyzer_variables *var);
void	clear_ast_analyzer_var(t_ast_analyzer_variables *var);
int		parse_to_ast_analyzer_var(
			t_token_stream *ts,
			t_ast_analyzer_variables *var);
#endif