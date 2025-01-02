/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:38:11 by chakim            #+#    #+#             */
/*   Updated: 2025/01/02 01:00:44 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "get_args.h"

/*
rl_gets() is readline from prompt and save histories wrote.
is_valid_builtins(); checks if cmd is valid or not.
if it is valid, it's parsed to exe_func. Unless, return 1 error code.
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

int	is_valid_builtins(char *cmd)
{
	int	status;

	if (ft_strcmp("echo", cmd) == 0)
	{
		//will implement exe function
		//Will implement if statement for checking -n option.
	}
	else if (ft_strcmp("cd", cmd) == 0)
	{
		//will implement exe function
	}
	else if (ft_strcmp("pwd", cmd) == 0)
	{
		//will implement exe function
	}
	else if (ft_strcmp("export", cmd) == 0)
	{
		//will implement exe function
	}
	else if (ft_strcmp("unset", cmd) == 0)
	{
		//will implement exe function
	}
	else if (ft_strcmp("env", cmd) == 0)
	{
		//will implement exe function
	}
	else if (ft_strcmp("exit", cmd) == 0)
	{
		//will implement exe function
	}
	else
		return (1);
}
