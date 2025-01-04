/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:50:57 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/04 19:35:35 by chakim           ###   ########.fr       */
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

static char	*create_new_env(char *name, char *value)
{
	char	*env;
	size_t	name_len;
	size_t	value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	env = malloc(name_len + value_len + 2);
	if (!env)
		return (NULL);
	ft_strlcpy(env, name, name_len + 1);
	ft_strlcat(env, "=", name_len + value_len + 2);
	ft_strlcat(env, value, name_len + value_len + 2);
	return (env);
}

/*
ms_setenv - Set or update an environment variable in the environment array.

This function searches for an environment variable with the specified `name`
within the NULL-terminated array of environment variables (`envp`).
If the variable is found, its value is updated to the provided `value`.
If the variable does not exist, the environment array is reallocated to
accommodate the new variable, which is then added to the array.

This function returns `SUCCESS` (0) if the operation completes without errors or
`FAILURE` (1) if a memory allocation error occurs or if the new environment
variable cannot be created.
*/
int	ms_setenv(char *name, char *value, char ***envp)
{
	size_t	name_len;
	size_t	envp_idx;
	void	*temp;

	name_len = ft_strlen(name);
	envp_idx = -1;
	while ((*envp)[++envp_idx])
		if (!ft_memcmp(name, (*envp)[envp_idx], name_len))
			break ;
	if (!(*envp)[envp_idx])
	{
		temp = ft_realloc(*envp, sizeof(size_t) * (envp_idx + 1),
				sizeof(size_t) * (envp_idx + 2));
		if (!temp)
			return (FAILURE);
		*envp = temp;
		(*envp)[envp_idx + 1] = NULL;
	}
	temp = create_new_env(name, value);
	if (!temp)
		return (FAILURE);
	if ((*envp)[envp_idx])
		free((*envp)[envp_idx]);
	(*envp)[envp_idx] = temp;
	return (SUCCESS);
}
