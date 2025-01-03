/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:38:11 by chakim            #+#    #+#             */
/*   Updated: 2025/01/03 17:34:11 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "../include/get_args.h"

/*
rl_gets() is readline from prompt and save histories wrote.
is_valid_builtins(); checks if cmd is valid or not.
if it is valid, it's parsed to exe_func and return 0. Unless, return 1 error code.
The status value will get status of return code.
There are 7 builtins to implement. only echo needs to do that with -n option.
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

int	is_valid_builtins(t_command *command)
{
	if (ft_strcmp("echo", command->cmd) == 0)
		return (ms_echo(command->args));
	else if (ft_strcmp("cd", command->cmd) == 0)
		return (ms_cd(command->args));
	else if (ft_strcmp("export", command->cmd) == 0)
		return (ms_export(command->args));
	else if (ft_strcmp("unset", command->cmd) == 0)
		return (ms_unset(command->args));
	else if (ft_strcmp("env", command->cmd) == 0)
		return (ms_env(command->args));
	else if (ft_strcmp("exit", command->cmd) == 0)
		return (ms_exit(command->args));
	else
		return (1);
}
