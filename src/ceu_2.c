/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 19:17:46 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ceu.h"
#include "ceu_parser.h"
#include "generic_array.h"
#include "token.h"
#include "wrapper.h"

t_ceu	*create_ceu_from_stream(t_token_stream *stream)
{
	t_ceu_var	ceu_var;
	t_ceu		*ceu;

	if (init_ceu_var(&ceu_var))
		return (NULL);
	if (parse_to_ceu_var(stream, &ceu_var))
	{
		clear_ceu_var(&ceu_var);
		return (NULL);
	}
	if (!(peek_token_stream(stream, 0)
			&& peek_token_stream(stream, 0)->type == TOKEN_NONE))
		--stream->offset;
	ceu = malloc(sizeof(t_ceu));
	if (!ceu)
	{
		clear_ceu_var(&ceu_var);
		return (NULL);
	}
	ceu->ir_arr = (t_in_redir **)detach_gen_arr(ceu_var.ir_arr);
	ceu->or_arr = (t_out_redir **)detach_gen_arr(ceu_var.or_arr);
	ceu->argv = (char **)detach_gen_arr(ceu_var.argv);
	return (ceu);
}
