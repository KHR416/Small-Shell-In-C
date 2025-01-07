/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:38:11 by chakim            #+#    #+#             */
/*   Updated: 2025/01/06 09:00:24 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "minishell.h"

/*
rl_gets() is readline from prompt and save histories wrote.

To avoid memory leaks, the returned string should be properly freed.
*/
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
