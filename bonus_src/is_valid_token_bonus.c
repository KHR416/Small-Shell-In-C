/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:24:30 by chakim            #+#    #+#             */
/*   Updated: 2025/03/25 16:40:20 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "token.h"

int	is_input_redirect_token(t_token_type type)
{
	return (type == TOKEN_INPUT_REDIRECT || type == TOKEN_HERE_DOC);
}

int	is_output_redirect_token(t_token_type type)
{
	return (type == TOKEN_OUTPUT_REDIRECT || type == TOKEN_APPEND_REDIRECT);
}

int	is_redirect_token(t_token_type type)
{
	return (is_input_redirect_token(type) || is_output_redirect_token(type));
}

int	is_ceu_token(t_token_type type)
{
	return (type == TOKEN_LITERAL || is_redirect_token(type));
}

int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND_OPERATOR || \
		type == TOKEN_OR_OPERATOR);
}
