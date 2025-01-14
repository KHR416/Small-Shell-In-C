/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/01/14 18:39:17 by chakim           ###   ########.fr       */
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
	char	*arr;

	arr = "env";
	i = 0;
	while (ft_strcmp(args[i], arr) == 0)
		i++;
	if (args[i] == NULL)
	{
		env = var->envp;
		while (*env != NULL)
		{
			if (is_equal_exist(*env))
				printf("%s\n", *env);
			++env;
		}
		return (SUCCESS);
	}
	else
	{
		while ()
	}
}
