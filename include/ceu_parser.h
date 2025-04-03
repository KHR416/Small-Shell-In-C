/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:43:53 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 18:45:10 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CEU_PARSER_H
# define CEU_PARSER_H
# include "generic_array.h"
# include "token.h"

typedef struct s_ceu_var
{
	t_gen_arr	*ir_arr;
	t_gen_arr	*or_arr;
	t_gen_arr	*argv;
}	t_ceu_var;

int		init_ceu_var(t_ceu_var *var);
void	clear_ceu_var(t_ceu_var *var);
int		append_in_redir(t_token_stream *stream, t_ceu_var *var);
int		append_out_redir(t_token_stream *stream, t_ceu_var *var);
int		parse_to_ceu_var(t_token_stream *stream, t_ceu_var *var);
#endif