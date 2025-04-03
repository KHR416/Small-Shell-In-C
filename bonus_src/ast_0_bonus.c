/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:10:31 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/21 13:34:05 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "libft.h"
#include <stdlib.h>

t_ast	*create_ast_node(void)
{
	return (ft_calloc(1, sizeof(t_ast)));
}

void	destroy_ast_node(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CEU)
		destroy_ceu(node->data[0].ceu);
	free(node);
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
