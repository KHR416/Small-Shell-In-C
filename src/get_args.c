/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:38:11 by chakim            #+#    #+#             */
/*   Updated: 2024/12/29 23:39:20 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_args.h"

char	*rl_gets(void)
{
	static char	*line_read;

	line_read = NULL;
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("minishell > ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int	is_valid_builtins(char *cmd)
{
	
}
