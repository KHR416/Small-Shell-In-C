/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceu_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:43:45 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/27 18:12:00 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ceu.h"
#include "ceu_parser.h"
#include "ms_def.h"
#include "wrapper.h"

int	init_ceu_var(t_ceu_var *var)
{
	var->ir_arr = create_gen_arr();
	if (!var->ir_arr)
		return (FAILURE);
	var->or_arr = create_gen_arr();
	if (!var->or_arr)
	{
		destroy_gen_arr(var->ir_arr, NULL);
		return (FAILURE);
	}
	var->argv = create_gen_arr();
	if (!var->argv)
	{
		destroy_gen_arr(var->ir_arr, NULL);
		destroy_gen_arr(var->or_arr, NULL);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	clear_ceu_var(t_ceu_var *var)
{
	destroy_gen_arr(var->ir_arr, destroy_in_redir_wrap);
	var->ir_arr = NULL;
	destroy_gen_arr(var->or_arr, destroy_out_redir_wrap);
	var->or_arr = NULL;
	destroy_gen_arr(var->argv, free);
	var->argv = NULL;
}

int	append_in_redir(t_token_stream *stream, t_ceu_var *var)
{
	t_token		*token;
	t_in_redir	*temp_in_redir;

	token = read_token_stream(stream);
	if (!peek_token_stream(stream, -2))
		return (FAILURE);
	if (peek_token_stream(stream, -2)->type == TOKEN_INPUT_REDIRECT)
		temp_in_redir = create_in_redir(IR_DEFAULT, token->data);
	else
		temp_in_redir = create_in_redir(IR_HERE_DOC, token->data);
	if (!temp_in_redir)
		return (FAILURE);
	if (append_gen_arr(var->ir_arr, temp_in_redir, NULL))
	{
		destroy_in_redir(temp_in_redir);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	append_out_redir(t_token_stream *stream, t_ceu_var *var)
{
	t_token		*token;
	t_out_redir	*temp_out_redir;

	token = read_token_stream(stream);
	if (!peek_token_stream(stream, -2))
		return (FAILURE);
	if (peek_token_stream(stream, -2)->type == TOKEN_OUTPUT_REDIRECT)
		temp_out_redir = create_out_redir(OR_DEFAULT, token->data);
	else
		temp_out_redir = create_out_redir(OR_APPEND, token->data);
	if (!temp_out_redir)
		return (FAILURE);
	if (append_gen_arr(var->or_arr, temp_out_redir, NULL))
	{
		destroy_out_redir(temp_out_redir);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	parse_to_ceu_var(t_token_stream *stream, t_ceu_var *var)
{
	t_token	*token;

	token = read_token_stream(stream);
	if (!token)
		return (FAILURE);
	while (token && is_ceu_token(token->type))
	{
		if (is_input_redirect_token(token->type))
		{
			if (append_in_redir(stream, var))
				return (FAILURE);
		}
		else if (is_output_redirect_token(token->type))
		{
			if (append_out_redir(stream, var))
				return (FAILURE);
		}
		else
		{
			if (append_gen_arr(var->argv, token->data, ft_strdup_wrap))
				return (FAILURE);
		}
		token = read_token_stream(stream);
	}
	return (SUCCESS);
}
