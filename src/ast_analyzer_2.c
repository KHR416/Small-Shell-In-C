/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_analyzer_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 19:44:57 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_def.h"
#include "astree.h"
#include "token.h"
#include "ast_analyzer.h"

t_ast	*ast_analyzer(t_token_stream *ts)
{
	t_ast_analyzer_variables	var;
	t_ast						*root;

	if (init_ast_analyzer_var(&var))
		return (NULL);
	if (parse_to_ast_analyzer_var(ts, &var))
	{
		clear_ast_analyzer_var(&var);
		return (NULL);
	}
	root = stack_top(var.operand_stack);
	stack_pop(var.operand_stack, NULL);
	clear_ast_analyzer_var(&var);
	return (root);
}
