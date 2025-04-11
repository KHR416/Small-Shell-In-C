/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:10:31 by wchoe             #+#    #+#             */
/*   Updated: 2025/04/11 15:21:22 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "libft.h"

int	is_operator_node(t_node_type type)
{
	return (type == NODE_PIPE || type == NODE_AND || type == NODE_OR);
}

int	op_cmp(t_node_type type1, t_node_type type2)
{
	if (type1 == type2
		|| ((type1 == NODE_AND || type1 == NODE_OR)
		&& (type2 == NODE_AND || type2 == NODE_OR)))
		return (0);
	if (type1 == NODE_PIPE && (type2 == NODE_AND || type2 == NODE_OR))
		return (1);
	return (-1);
}

int	cmp_not_same(t_node_type type, t_node_type type_open)
{
	if (type != type_open)
		return (0);
	return (-1);
}
