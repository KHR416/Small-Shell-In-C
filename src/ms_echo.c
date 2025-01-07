/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/01/06 09:01:14 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

/*
	This function does simply print args to stdout from prompt.
	After print last argument, newline should follow.
*/
int	ms_echo(char **args)
{
	int	i;

	if (args[1] == NULL)
	{
		printf('\n');
		return (SUCCESS);
	}
	i = 1;
	while (args[i + 1] != NULL)
	{
		printf("%s ", args[i]);
		++i;
	}
	printf("%s\n", args[i]);
	return (SUCCESS);
}
