/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/25 16:35:45 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <libft.h>
#include <stdio.h>

#ifdef DEBUG
int	print_in_redir(t_in_redir *ir)
{
	if (!ir)
		return (FAILURE);
	if (ir->type == IR_DEFAULT)
		fprintf(stderr, "%s", "<");
	else
		fprintf(stderr, "%s", "<<");
	fprintf(stderr, "%s\n", ir->name);
	return (SUCCESS);
}

int	print_ir_list(t_list *ir)
{
	while (ir)
	{
		print_in_redir(ir->content);
		ir = ir->next;
	}
	return (SUCCESS);
}

int	print_out_redir(t_out_redir *or)
{
	if (!or)
		return (FAILURE);
	if (or->type == OR_DEFAULT)
		fprintf(stderr, "%s", ">");
	else
		fprintf(stderr, "%s", ">>");
	fprintf(stderr, "%s\n", or->name);
	return (SUCCESS);
}

int	print_or_list(t_list *or)
{
	while (or)
	{
		print_out_redir(or->content);
		or = or->next;
	}
	return (SUCCESS);
}

int	print_argv(char **argv)
{
	if (!argv)
		return (FAILURE);
	for (char **it = argv; *it; ++it)
		fprintf(stderr, "argv[%zu]: %s\n", it - argv, *it);
	return (SUCCESS);
}

int	print_ceu(t_ceu *ceu)
{
	if (!ceu)
		return (FAILURE);
	if (print_ir_list(ceu->ir_list))
		return (FAILURE);
	if (print_or_list(ceu->or_list))
		return (FAILURE);
	if (print_argv(ceu->argv))
		return (FAILURE);
	return (SUCCESS);
}
#endif
