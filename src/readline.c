/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:38:11 by chakim            #+#    #+#             */
/*   Updated: 2025/02/25 20:45:22 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_readline.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>

/*
rl_gets() is readline from prompt and save histories wrote.

To avoid memory leaks, the returned string should be properly freed.
*/
char	*rl_gets(void)
{
	char	*str;

	#ifndef MEMCHECK
	str = readline(MS_PROMPT);
	if (str && *str)
		add_history(str);
	#else
	str = NULL;
	char	buf[1024];
	printf("%s", MS_PROMPT);
	if (!fgets(buf, 1024, stdin))
		return (NULL);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';
	str = strdup(buf);
	#endif
	return (str);
}
