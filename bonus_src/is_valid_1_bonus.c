/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:08:35 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/27 21:05:22 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

void	print_error_unexpected_token(t_token_type type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", \
		STDERR_FILENO);
	print_token_type(type, STDERR_FILENO);
	ft_putendl_fd("`", STDERR_FILENO);
}
