/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:29:51 by chakim            #+#    #+#             */
/*   Updated: 2025/01/08 18:09:28 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ms_env(char **args, t_msvar *var)
{
	char	**env;
	int		i;
	char	*arr;

	arr = "env";
	i = 0;
	while (strcmp(args[i], arr) == 0)
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
		return 0;
	}
}
