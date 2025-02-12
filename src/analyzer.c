/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/10 18:33:07 by wchoe            ###   ########.fr       */
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
	// Only pipe_seg exist for mandatory
	destroy_pipe_seg(node->data->pipe_seg);
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

void	destroy_ast(t_ast *root)
{
	// Only one pipe_seg exist for mandatory.
	destroy_ast_node(root);
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
	// Only pipe_seg exist for mandatory
	root->type = NODE_PIPE_SEG;
	root->data->pipe_seg = create_pipe_seg(ts->arr, ts->arr + ts->len);
	if (!root->data->pipe_seg)
	{
		free(root);
		return (NULL);
	}
	return (root);
}
