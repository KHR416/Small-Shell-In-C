/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 17:04:14 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ceu.h"
#include <stdlib.h>
#include <libft.h>

t_in_redir	*create_in_redir(t_in_redir_type type, char *data)
{
	t_in_redir	*ir;

	if (!(type == IR_DEFAULT || type == IR_HERE_DOC))
		return (NULL);
	ir = malloc(sizeof(t_in_redir));
	if (!ir)
		return (NULL);
	ir->type = type;
	if (data)
		ir->name = ft_strdup(data);
	return (ir);
}

void	destroy_in_redir(t_in_redir *ir)
{
	free(ir->name);
	free(ir);
}

t_out_redir	*create_out_redir(t_out_redir_type type, char *data)
{
	t_out_redir	*or;

	if (!(type == OR_DEFAULT || type == OR_APPEND))
		return (NULL);
	or = malloc(sizeof(t_out_redir));
	if (!or)
		return (NULL);
	or->type = type;
	if (data)
		or->name = ft_strdup(data);
	return (or);
}

void	destroy_out_redir(t_out_redir *or)
{
	free(or->name);
	free(or);
}
