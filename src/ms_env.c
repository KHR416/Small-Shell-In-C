/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/01/07 20:27:32 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	ms_env(char **args, t_msvar *var)
{
	char	**env;
	int		i;

	i = 0;
	while (args[i] != "env")
		i++;
	if (args[i] == NULL)
	{
		env = var->envp;
		while (*env != NULL)
		{
			printf("%s\n", *env);
			++env;
		}
		return (SUCCESS);
	}
	else
	{
		// execute args[i] to args[n]
	}
}
