/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:47:19 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 19:13:52 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

void	print_token_type(t_token_type type, int fd)
{
	if (type == TOKEN_NONE)
		ft_putstr_fd("new_line", fd);
	else if (type == TOKEN_LITERAL)
		ft_putstr_fd("literal", fd);
	else if (type == TOKEN_PIPE)
		ft_putstr_fd("|", fd);
	else if (type == TOKEN_INPUT_REDIRECT)
		ft_putstr_fd("<>", fd);
	else if (type == TOKEN_HERE_DOC)
		ft_putstr_fd("<<", fd);
	else if (type == TOKEN_OUTPUT_REDIRECT)
		ft_putstr_fd(">", fd);
	else if (type == TOKEN_APPEND_REDIRECT)
		ft_putstr_fd(">>", fd);
	else if (type == TOKEN_AND_OPERATOR)
		ft_putstr_fd("&&", fd);
	else if (type == TOKEN_OR_OPERATOR)
		ft_putstr_fd("||", fd);
	else if (type == TOKEN_PARENTHESIS_OPEN)
		ft_putstr_fd("(", fd);
	else if (type == TOKEN_PARENTHESIS_CLOSE)
		ft_putstr_fd(")", fd);
	else
		ft_putstr_fd("unknown token", fd);
}
