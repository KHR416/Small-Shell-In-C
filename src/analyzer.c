/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/26 23:22:10 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

t_ast	*create_ast_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ast));
	return (node);
}

void	destroy_ast_node(t_ast *node)
{
	if (!node)
		return ;
	// free(node->left);
	// free(node->right);
	// free(node->data);
	free(node);
}

int	search_ast(t_ast *root, int order, int (*func)())
{
	if (!root)
		return (SUCCESS);
	// TODO: create post-order DFS
	if (order == 0)	// CFLAG dummy. remove it later.
		return (FAILURE);
	else
		func(root);
	return (SUCCESS);
}

t_ast	*analyzer(t_token_stream *ts)
{
	// TODO: create ast
	// lexicon priority: '\', "'> '&&, ||' > '|' > '>, >>, <, <<'
	// syntax priority: suffix > prefix
	t_ast			*root;

	root = create_ast_node();
	if (!root)
		return (NULL);
	// interpret_quote(token_arr);
	// interpret_pipe(root, token_arr);
	// interpret_redir_out(root, token_arr);
	// interpret_redir_in(root, token_arr);
	// interpret_cmd(root, token_arr);
	destroy_token_stream(ts);
	return (root);
}
