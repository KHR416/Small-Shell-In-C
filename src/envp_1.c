/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:50:57 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/06 13:55:03 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include "minishell.h"
#include "buffer.h"

static char	*create_new_env(char *name, char *value)
{
	t_buf	*buf;

	buf = create_buf();
	if (!buf)
		return (NULL);
	cat_buf(buf, name);
	if (value)
	{
		append_buf(buf, '=');
		cat_buf(buf, value);
	}
	return (detach_buf(buf));
}

static int	is_valid_name(char *name)
{
	if (ft_isdigit(*name))
		return (0);
	while (*name)
	{
		if (!(ft_isalnum(*name) || *name == '_'))
			return (0);
		++name;
	}
	return (1);
}

static int	realloc_envp(char ***envp, size_t old_memb_cap, size_t new_memb_cap)
{
	void	*temp;

	temp = ft_realloc(*envp, sizeof(size_t) * old_memb_cap,
			sizeof(size_t) * new_memb_cap);
	if (!temp)
		return (FAILURE);
	*envp = temp;
	return (SUCCESS);
}

/*
ms_setenv - Set or update an environment variable in the environment array.

DESCRIPTION
This function searches for an environment variable with the specified `name`
within the NULL-terminated array of environment variables (`envp`).
If the variable is valid and found, its value is updated to the provided
`value`. If the variable does not exist, the environment array is reallocated to
accommodate the new variable, which is then added to the array.

RETURN
`SUCCESS` (0) if the operation completes without errors or `FAILURE` (1)
if `name` is invalid, if a memory allocation error occurs or if the new
environment variable cannot be create.

NOTES
The argument `name` must consist solely of uppercase letters, digits, and the
underscore ('_') and do not begin with a digit. If `name` contains other
characters or starts with a digit, it is considered invalid.
In the case that `value` is `NULL`, it will clear the equal sign and its value
if the env is exist or will export env name without the equal sign and value.
*/
int	ms_setenv(char *name, char *value, char ***envp)
{
	size_t	env_name_len;
	size_t	envp_idx;
	void	*temp;

	if(!is_valid_name(name))
		return (FAILURE);
	
	envp_idx = -1;
	while ((*envp)[++envp_idx])
	{
		env_name_len = 0;
		// while ((*envp)[env_name_len] && (*envp)[env_name_len] != '=')
	if (!ft_strncmp((*envp)[envp_idx], name, env_name_len) && \
    ((*envp)[envp_idx][env_name_len] == '=' || (*envp)[envp_idx][env_name_len] == '\0'))
			++env_name_len;
		if (!ft_memcmp(name, (*envp)[envp_idx], env_name_len))
			break ;
	}
	if (!(*envp)[envp_idx])
	{
		if (realloc_envp(envp, envp_idx + 1, envp_idx + 2))
			return (FAILURE);
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
