/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/14 23:14:55 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>
#include "generic_array.h"

void	destroy_pipe_seg(t_pipe_seg *ps)
{
	if (!ps)
		return ;
	if (ps->type == PS_CEU)
		destroy_ceu(ps->data.ceu);
	else
		destroy_ast(ps->data.ast);
	free(ps);
}
void	destroy_pipe_seg_wrap(void *ps)
{
	destroy_pipe_seg(ps);
}

t_pipe_seg	*create_pipe_seg(void)
{
	t_pipe_seg	*ps = malloc(sizeof(t_pipe_seg));
	if (!ps)
		return (NULL);
	return (ft_memset(ps, 0, sizeof(t_pipe_seg)));
}
t_pipe_seg	**create_pipe_seg_arr(t_token_stream *stream)
{
	t_gen_arr	*pipe_seg_arr = create_gen_arr();
	t_pipe_seg	*pipe_seg = NULL;
	while (1)
	{
		if (is_ceu(stream->arr[stream->offset].type))
		{
			pipe_seg = create_pipe_seg();
			pipe_seg->type = PS_CEU;
			pipe_seg->data.ceu = create_ceu_from_stream(stream);
			if (!pipe_seg->data.ceu)
			{
				destroy_gen_arr(pipe_seg_arr, destroy_pipe_seg_wrap);
				return (NULL);
			}
			append_gen_arr(pipe_seg_arr, pipe_seg, NULL);
		}
		else if (stream->arr[stream->offset].type == TOKEN_PARENTHESIS_OPEN)
		{
			pipe_seg = create_pipe_seg();
			pipe_seg->type = PS_AST;
			++stream->offset;
			pipe_seg->data.ast = analyzer(stream);
			if (!pipe_seg->data.ast)
			{
				destroy_gen_arr(pipe_seg_arr, destroy_pipe_seg_wrap);
				return (NULL);
			}
			append_gen_arr(pipe_seg_arr, pipe_seg, NULL);
		}
		else if (stream->arr[stream->offset].type == TOKEN_PIPE)
			++stream->offset;
		else
			break ;
	}
	return ((t_pipe_seg **)detach_gen_arr(pipe_seg_arr));
}
