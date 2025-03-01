/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:54:05 by chakim            #+#    #+#             */
/*   Updated: 2025/03/01 17:06:11 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_equal_exist(char *str)
{
	return (strchr(str, '=') != NULL);
}

static char *get_first_line(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		++i;
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	i = 0;
	while(str[i] != '=' && str[i] != '\0')
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}

static char	*get_second_line(char *str)
{
	char	*equal;

	if (!str)
		return (NULL);
	equal = ft_strchr(str, '=');
	if (equal == NULL)
		return (ft_strdup(""));
	else
		return (ft_strdup(equal + 1));
}

static void	print_all_env(t_msvar *var)
{
	char	**env;
	char	*first_line;
	char	*second_line;

	env = var->envp;
	while (*env != NULL)
	{
		if (is_equal_exist(*env))
		{
			first_line = get_first_line(*env);
			second_line = get_second_line(*env);
			if (!first_line || !second_line)
			{
				free(first_line);
				free(second_line);
				return ;
			}
			printf("declare -x %s=\"%s\"\n", first_line, second_line);
			free(first_line);
			free(second_line);
		}
		else
			printf("declare -x %s\n", *env);
		++env;
	}
}

int	ms_export(char **args, t_msvar *var)
{
	char	*first_line;
	char	*second_line;
	int		i;

	i = 1;
	if (args[1] == NULL)
	{
		print_all_env(var);
		return (SUCCESS);
	}
	else
	{
		while (args[i] != NULL)
		{
			first_line = get_first_line(args[i]);
			second_line = get_second_line(args[i]);
			if (!first_line || !second_line)
			{
				free(first_line);
				free(second_line);
				continue ;
			}
			ms_setenv(first_line, second_line, &var->envp);
			free(first_line);
			free(second_line);
			++i;
		}
	}
	return (SUCCESS);
}
