/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:10:31 by wchoe             #+#    #+#             */
/*   Updated: 2025/04/12 17:28:04 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "libft.h"

int	is_operator_node(t_node_type type)
{
	return (type == NODE_PIPE || type == NODE_AND || type == NODE_OR);
}

int	get_operator_precendence(t_node_type type)
{
	if (type == NODE_PARANTHESIS_OPEN)
		return (0);
	if (type == NODE_AND || type == NODE_OR)
		return (1);
	if (type == NODE_PIPE)
		return (2);
	return (-1);
}

int	op_cmp(t_node_type type1, t_node_type type2)
{
	return (get_operator_precendence(type1) - get_operator_precendence(type2));
}

int	cmp_not_same(t_node_type type, t_node_type type_open)
{
	if (type != type_open)
		return (0);
	return (-1);
}
