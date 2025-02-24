/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seg.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/24 16:03:06 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_SEG_H
# define PIPE_SEG_H
# include "ceu.h"
# include <sys/types.h>
# include <stdio.h>

typedef struct s_pipeline_segment
{
	t_list	*ceu_list;
}	t_pipe_seg;


size_t		pipe_seg_len(t_token *iter_begin, t_token *iter_end);
void		destroy_pipe_seg(t_pipe_seg *ps);
t_pipe_seg	*create_pipe_seg(t_token *iter_begin, t_token *iter_end);
int			print_pipe_seg(t_pipe_seg *ps);
int			pipe_seg_exec(t_pipe_seg *ps, t_msvar *msvar);
#endif	// PIPE_SEG_H