/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:22:59 by chakim            #+#    #+#             */
/*   Updated: 2025/02/27 07:21:36 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <unistd.h>
#ifdef DEBUG
# include "ceu.h"
# include "pipe_seg.h"
#endif	//DEBUG
#include "astree.h"

int	ms_var_init(int argc, char **argv, char **envp, t_msvar *msvar)
{
	msvar->argc = argc;
	msvar->argv = argv;
	msvar->envp = ms_envpcpy(envp);
	if (!msvar->envp)
		return (FAILURE);
	msvar->exit_status = 0;
	msvar->ttydup[0] = dup(STDIN_FILENO);
	msvar->ttydup[1] = dup(STDOUT_FILENO);
	#ifdef DEBUG
	msvar->ceu = NULL;
	msvar->ps = NULL;
	#endif
	msvar->ast = NULL;
	return (SUCCESS);
}

void	clear_ttydup(t_msvar *msvar)
{
	if (msvar->ttydup[0] != -1)
		close(msvar->ttydup[0]);
	msvar->ttydup[0] = -1;
	if (msvar->ttydup[1] != -1)
		close(msvar->ttydup[1]);
	msvar->ttydup[1] = -1;
}

int	restore_ttydup(t_msvar *msvar)
{
	if (!isatty(STDIN_FILENO))
		dup2(msvar->ttydup[0], STDIN_FILENO);
	if (!isatty(STDOUT_FILENO))
		dup2(msvar->ttydup[1], STDOUT_FILENO);
	return (SUCCESS);
}

void	clear_msvar(t_msvar *msvar)
{
	ms_envp_destroy(msvar->envp);
	msvar->envp = NULL;
	clear_ttydup(msvar);
	#ifdef DEBUG
	destroy_ceu(msvar->ceu);
	msvar->ceu = NULL;
	destroy_pipe_seg(msvar->ps);
	msvar->ps = NULL;
	#endif	//DEBUG
	destroy_ast(msvar->ast);
	msvar->ast = NULL;
}
