/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:38:11 by chakim            #+#    #+#             */
/*   Updated: 2025/02/24 21:27:08 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_readline.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>

/*
rl_gets() is readline from prompt and save histories wrote.

To avoid memory leaks, the returned string should be properly freed.
*/
char	*rl_gets(void)
{
	char	*str;
	#ifdef MEMCHECK
	char	buf[1024];
	#endif

	#ifndef MEMCHECK
	str = readline("minishell > ");
	if (str && *str)
		add_history(str);
	#else
	fgets(buf, 1024, stdin);
	buf[strlen(buf) - 1] = '\0';
	str = strdup(buf);
	#endif
	return (str);
}
