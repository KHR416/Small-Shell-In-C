/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:54:05 by chakim            #+#    #+#             */
/*   Updated: 2025/01/06 09:02:18 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static void	print_all_env(char **args, t_msvar *var)
{
	char	**env;
	char	*line;

	env = var->envp;
	while(*env != NULL)
	{
		printf("declare -x %s=""%s""", );
		++env;
	}
}

int	ms_export(char **args, t_msvar *var)
{
	if (args[1] == NULL)
	{
		print_all_env(args, var);
		return (SUCCESS);
	}
	else
	{
		// execute args[1] to args[n]
	}
}
