/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:38:11 by chakim            #+#    #+#             */
/*   Updated: 2025/01/04 20:39:46 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "get_args.h"
#include "minishell.h"

/*
rl_gets() is readline from prompt and save histories wrote.

To avoid memory leaks, the returned string should be properly freed.
*/
char	*rl_gets(void)
{
	static char	*line_read;

	line_read = NULL;
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("minishell > ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

t_command	*parse_input(char *input)
{
	// this is prototype, so need implement for coplicated situations
	t_command	*cmd;
	char**		tokens;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd = ft_strdup(tokens[0]);
	cmd->args = tokens;
	return (cmd);
}
/*
	is_valid_builtins(); checks if cmd is valid or not.
	if it is valid, it's parsed to exe_func and return 0. Unless, return error code.
	There are 7 builtins to implement. only echo needs to do that with -n option.
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
