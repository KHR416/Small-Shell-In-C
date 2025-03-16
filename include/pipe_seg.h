/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seg.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/14 22:43:24 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_SEG_H
# define PIPE_SEG_H
# include "ceu.h"
# include <sys/types.h>
# include <stdio.h>
# include "astree.h"
typedef enum e_pipeline_segment_type
{
	PS_NONE = 0,
	PS_CEU = 1 << 0,
	PS_AST = 1 << 1,
}	t_pipe_seg_type;

typedef union u_pipeline_segment_data
{
	struct s_ast_node	*ast;
	t_ceu				*ceu;
}	t_pipe_seg_data;


typedef struct s_pipeline_segment
{
	t_pipe_seg_type	type;
	t_pipe_seg_data	data;
}	t_pipe_seg;

size_t		pipe_seg_len(t_pipe_seg **ps);
void		destroy_pipe_seg(t_pipe_seg *ps);
t_pipe_seg	**create_pipe_seg_arr(t_token_stream *stream);
int			print_pipe_seg_arr(t_pipe_seg **ps);
int			pipe_seg_exec(t_pipe_seg **ps, t_msvar *msvar);
#endif	// PIPE_SEG_H