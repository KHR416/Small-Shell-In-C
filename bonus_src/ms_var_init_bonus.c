/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:22:59 by chakim            #+#    #+#             */
/*   Updated: 2025/04/03 21:21:53 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <unistd.h>
#include "astree.h"
#include "generic_array.h"
#include "wrapper.h"

static int	clear_msvar_and_return_failure(t_msvar *msvar)
{
	clear_msvar(msvar);
	return (FAILURE);
}

int	ms_var_init(int argc, char **argv, char **envp, t_msvar *msvar)
{
	ft_memset(msvar, 0, sizeof(t_msvar));
	msvar->argc = argc;
	msvar->argv = argv;
	msvar->envp = ms_envpcpy(envp);
	if (!msvar->envp)
		return (FAILURE);
	msvar->ttydup[0] = dup(STDIN_FILENO);
	msvar->ttydup[1] = dup(STDOUT_FILENO);
	msvar->buf = create_buf();
	if (!msvar->buf)
		return (clear_msvar_and_return_failure(msvar));
	msvar->command_buf = create_buf();
	if (!msvar->command_buf)
		return (clear_msvar_and_return_failure(msvar));
	msvar->cw_backup = ms_getcwd(msvar);
	if (!msvar->cw_backup)
		return (clear_msvar_and_return_failure(msvar));
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
