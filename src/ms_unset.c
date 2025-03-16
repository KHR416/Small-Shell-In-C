/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:23:36 by chakim            #+#    #+#             */
/*   Updated: 2025/03/14 18:24:58 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	**find_env(char *env_str, char **envp)
{
	size_t	str_len;
	int		i;

	str_len = ft_strlen(env_str);
	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp(env_str, envp[i], str_len) == 0 && envp[i][str_len] == '=')
			return (envp + i);
		++i;
	}
	return (NULL);
}

int	ms_unset(char **args, t_msvar *var)
{
	int		i;
	char	**hit;

	i = 1;
	size_t	envp_len = 0;
	while (var->envp[envp_len])
		++envp_len;
	while (args[i] != NULL)
	{
		hit = find_env(args[i], var->envp);
		if (hit)
		{
			free(*hit);
			ft_memmove(hit, hit + 1, (envp_len - (hit - var->envp)) * sizeof(char *));
			--envp_len;
		}
		++i;
	}
	return (SUCCESS);
}
