/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/03/01 17:04:03 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ms_env(char **args, t_msvar *var)
{
	char	**env;

	if (args[1])
	{
		ft_putendl_fd("minishell: env: too many arguments.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	env = var->envp;
	while (*env != NULL)
	{
		if (ft_strchr(*env, '='))
			printf("%s\n", *env);
		++env;
	}
	return (EXIT_SUCCESS);
}
