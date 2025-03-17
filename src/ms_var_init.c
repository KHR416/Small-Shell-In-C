/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:22:59 by chakim            #+#    #+#             */
/*   Updated: 2025/03/17 16:42:17 by wchoe            ###   ########.fr       */
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
	msvar->ceu_arr = NULL;
	#endif
	msvar->ast = NULL;
	msvar->heredoc_count = 0;
	msvar->buf = create_buf();
	if (!msvar->buf)
	{
		// Exception
	}
	msvar->command_buf = create_buf();
	if (!msvar->command_buf)
	{
		// Exception
	}
	msvar->cw_backup = ms_getcwd(msvar);
	msvar->old_cw_backp = NULL;
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
#include "generic_array.h"

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
	destroy_void_arr(msvar->ceu_arr, destroy_ceu);
	msvar->ceu_arr = NULL;
	#endif	//DEBUG
	destroy_ast(msvar->ast);
	msvar->ast = NULL;
	destroy_buf(msvar->buf);
	msvar->buf = NULL;
	destroy_buf(msvar->command_buf);
	msvar->command_buf = NULL;
	free(msvar->cw_backup);
	msvar->cw_backup = NULL;
	free(msvar->old_cw_backp);
	msvar->old_cw_backp = NULL;
}
