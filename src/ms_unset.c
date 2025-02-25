/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:23:36 by chakim            #+#    #+#             */
/*   Updated: 2025/02/25 16:51:24 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	find_env(char *env_str, char **envp)
{
	size_t	str_len;
	int		i;

	str_len = ft_strlen(env_str);
	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp(env_str, envp[i], str_len) == 0 && envp[i][str_len] == '=')
			return (SUCCESS);
		++i;
	}
	return (FAILURE);
}

void	ms_env_unset(char **envp, char *to_free)
{
	size_t	str_len;
	int		i;
	int		j;
	
	i = 0;
	while (envp[i] != NULL)
	{
		str_len = ft_strlen(to_free);
		if (strncmp(to_free, envp[i], str_len) == 0 && \
		envp[i][str_len] == '=')
		{
			free(envp[i]);
			j = i;
			while (envp[j] != NULL)
			{
				envp[j] = envp[j + 1];
				++j;
			}
		}
		else
			++i;
	}
}

int	ms_unset(char **args, t_msvar *var)
{
	int	i;

	i = 1;
	if (args[1] == 1)
		return (SUCCESS);
	while (args[i] != NULL)
	{
		if (find_env(args[i], var->envp) == SUCCESS)
			ms_env_unset(var->envp, args[i]);
		++i;
	}
	return (SUCCESS);
}
