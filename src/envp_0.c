/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:50:57 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/05 20:25:07 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include "minishell.h"

/*
ms_envp_destroy - Frees a NULL-terminated array of environment variables.

This function takes a NULL-terminated array of pointers (`envp`) and frees each
individual string within the array. After all strings have been freed, the array
itself is also freed. This effectively destroys the entire environment variables
array, ensuring that all allocated memory is properly released.
*/
void	ms_envp_destroy(void **envp)
{
	size_t	idx;

	idx = 0;
	while (envp[idx])
		free(envp[idx++]);
	free(envp);
}

/*
ms_envpcpy - Create a deep copy of the environment variables array.

This function takes a NULL-terminated array of strings (`envp`) and creates
a deep copy of it. Each string in the original array is duplicated, and a new
array is allocated to hold the pointers to these duplicated strings.

If any memory allocation fails during the process, the function ensures that
all previously allocated memory is freed, and `NULL` is returned to indicate
the failure.
*/
char	**ms_envpcpy(char **envp)
{
	char	**copy;
	size_t	idx;
	size_t	len;

	len = 0;
	while (envp[len])
		++len;
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	idx = 0;
	while (envp[idx])
	{
		copy[idx] = ft_strdup(envp[idx]);
		if (!copy[idx])
		{
			ms_envp_destroy((void **)copy);
			return (NULL);
		}
		++idx;
	}
	copy[idx] = NULL;
	return (copy);
}

/*
ms_getenv - Retrieve the value of an environment variable by name.

This function searches through a NULL-terminated array of environment variables
(`envp`) to find a variable that matches the specified `name`.

If a matching environment variable is found, a pointer to its value is returned.
If no matching variable is found, the function returns `NULL`.
*/
char	*ms_getenv(char *name, char **envp)
{
	size_t	envp_idx;
	size_t	name_len;

	envp_idx = 0;
	name_len = ft_strlen(name);
	while (envp[envp_idx])
	{
		if (!ft_memcmp(name, envp[envp_idx], name_len))
			return (envp[envp_idx] + name_len + 1);
		++envp_idx;
	}
	return (NULL);
}
