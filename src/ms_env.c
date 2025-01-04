/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/01/04 21:20:46 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_args.h"
#include "minishell.h"

int	ms_env(char **args, t_msvar *var)
{
	char **env;

	if (args[1] == NULL)
	{
		env = var->envp;
		while(*env != NULL)
		{
			printf("%s\n", *env);
			++env;
		}
		return (0);
	}
	else
	{
		// execute args[1] to args[n]
	}
}
