/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:30:53 by chakim            #+#    #+#             */
/*   Updated: 2025/04/03 21:20:22 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "token.h"
#include "astree.h"
#include "minishell.h"
#include <signal.h>
#include "ms_signal.h"

int	g_ms_signal;

void	sigint_handler(int sig)
{
	g_ms_signal = sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler_control(int sig)
{
	g_ms_signal = sig;
	if (sig == SIGINT)
		printf("\n");
}

void	sigquit_hanlder(int sig)
{
	g_ms_signal = sig;
	rl_on_new_line();
	rl_redisplay();
	printf("  \b\b");
}
