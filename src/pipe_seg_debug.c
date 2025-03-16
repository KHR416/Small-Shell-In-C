/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seg_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/14 22:43:35 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <libft.h>
#include <stdio.h>

#ifdef DEBUG
int	print_pipe_seg(t_pipe_seg *ps)
{
	++ps;
	// if (!ps || !ps->ceu_list)
	// 	return (FAILURE);
	// for (t_list *it = ps->ceu_list; it; it = it->next)
	// {
	// 	if (it != ps->ceu_list)
	// 		fprintf(stderr, "====PIPE====\n");
	// 	if (print_ceu(it->content))
	// 		return (FAILURE);
	// }
	// return (SUCCESS);
	return (SUCCESS);
}
#endif
