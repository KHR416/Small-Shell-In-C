/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:58:20 by chakim            #+#    #+#             */
/*   Updated: 2025/03/22 16:50:32 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0)
		return (1);
	if (ft_strcmp("cd", cmd) == 0)
		return (1);
	if (ft_strcmp("export", cmd) == 0)
		return (1);
	if (ft_strcmp("unset", cmd) == 0)
		return (1);
	if (ft_strcmp("env", cmd) == 0)
		return (1);
	if (ft_strcmp("exit", cmd) == 0)
		return (1);
	if (ft_strcmp("pwd", cmd) == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **argv, t_msvar *var)
{
	if (ft_strcmp("echo", argv[0]) == 0)
	{
		if (!argv[1])
			return (ms_echo(argv));
		if (ft_strcmp("-n", argv[1]) == 0)
			return (ms_echo_n_option(argv));
		else
			return (ms_echo(argv));
	}
	if (ft_strcmp("cd", argv[0]) == 0)
		return (ms_cd(argv, var));
	if (ft_strcmp("export", argv[0]) == 0)
		return (ms_export(argv, var));
	if (ft_strcmp("unset", argv[0]) == 0)
		return (ms_unset(argv, var));
	if (ft_strcmp("env", argv[0]) == 0)
		return (ms_env(argv, var));
	if (ft_strcmp("exit", argv[0]) == 0)
		return (ms_exit(argv, var));
	return (ms_pwd(var));
}
