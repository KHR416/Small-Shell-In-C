/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:58:20 by chakim            #+#    #+#             */
/*   Updated: 2025/01/06 09:04:07 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
/*
	is_valid_builtins(); checks if cmd is valid or not.
	if it is valid, it's parsed to exe_func and return 0. Unless, return error code.
	There are 7 builtins implemented. only echo needs to do that with -n option.
*/
int	is_valid_builtins(t_command *command, t_msvar *var)
{
	if (ft_strcmp("echo", command->args[0]) == 0)
	{
		if (ft_strcmp("-n", command->args[1]) == 0)
			return (ms_echo_n_option(command->args));
		else
			return (ms_echo(command->args));
	}
	else if (ft_strcmp("cd", command->args[0]) == 0)
		return (ms_cd(command->args));
	else if (ft_strcmp("export", command->args[0]) == 0)
		return (ms_export(command->args, var));
	else if (ft_strcmp("unset", command->args[0]) == 0)
		return (ms_unset(command->args));
	else if (ft_strcmp("env", command->args[0]) == 0)
		return (ms_env(command->args, var));
	else if (ft_strcmp("exit", command->args[0]) == 0)
		return (ms_exit(command->args));
	else if (ft_strcmp("pwd", command->args[0]) == 0)
		return (ms_pwd());
	else
		return (FAILURE);
}
