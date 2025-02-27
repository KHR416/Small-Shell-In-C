/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 02:27:27 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/27 02:28:48 by wchoe            ###   ########.fr       */
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

int	ms_signal;

void	sigint_handler(int sig)
{
	ms_signal = sig;
	#ifndef MEMCHECK
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	#else
	fflush(stdin);
	printf("\n%s", MS_PROMPT);
	fflush(stdout);
	#endif
}

void	sig_handler_control(int sig)
{
	ms_signal = sig;
	if (sig == SIGINT)
		printf("\n");
}

void	sigquit_hanlder(int sig)
{
	ms_signal = sig;
	#ifndef MEMCHECK
	rl_on_new_line();
	rl_redisplay();
	printf("  \b\b");
	#else
	fflush(stdin);
	printf("  \b\b");
	fflush(stdout);
	// :LeniDunno:
	#endif
}

int	update_sigaction_interactive()
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = sigquit_hanlder;
	sigaction(SIGQUIT, &sa, NULL);
	return (SUCCESS);
}

int	update_sigaction_control()
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sig_handler_control;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (SUCCESS);
}

int	rollback_sigaction()
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (SUCCESS);
}
