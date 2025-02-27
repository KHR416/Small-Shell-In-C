/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/02/27 05:14:26 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_equal_exist(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	ms_env(char **args, t_msvar *var)
{
	char	**env;
	int		i;

	i = 0;
	while (args[i])
		++i;
	if (i > 1)
	{
		ft_putendl_fd("minishell: env: too many arguments.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	env = var->envp;
	while (*env != NULL)
	{
		if (is_equal_exist(*env))
			printf("%s\n", *env);
		++env;
	}
	return (EXIT_SUCCESS);
}
