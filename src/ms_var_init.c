/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:22:59 by chakim            #+#    #+#             */
/*   Updated: 2025/02/24 16:36:05 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

int	ms_var_init(int argc, char **argv, char **envp, t_msvar *var)
{
	var->argc = argc;
	var->argv = argv;
	var->envp = ms_envpcpy(envp);
	var->exit_status = 0;
	if (!var->envp)
		return (FAILURE);
	return (SUCCESS);
}

void	free_msvar(t_msvar *msvar)
{
	ms_envp_destroy(msvar->envp);
	msvar->envp = NULL;
}
