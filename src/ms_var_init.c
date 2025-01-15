/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:22:59 by chakim            #+#    #+#             */
/*   Updated: 2025/01/08 15:30:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_var_init(int argc, char **argv, char **envp, t_msvar *var)
{
	var->argc = argc;
	var->argv = argv;
	var->envp = ms_envpcpy(envp);
	if (!var->envp)
		return (FAILURE);
	return (SUCCESS);
}
