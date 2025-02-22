/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:54:05 by chakim            #+#    #+#             */
/*   Updated: 2025/02/21 15:42:59 by chakim           ###   ########.fr       */
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

static char *get_first_line(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i])
		i++;
	result = malloc(i);
	while(str[i] != '=')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*get_second_line(char *str)
{
	char	*result;
	char	*temp;
	int		i;

	temp = str;
	i = 0;
	while (*temp != '=')
		temp++;
	while (temp[i])
	{
		result[i] = temp[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static void	print_all_env(char **args, t_msvar *var)
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
			printf("declare -x %s=""%s""", first_line, second_line);
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
	int		i;
	int		j;

	while (ft_strcmp("export", args[i]) == 0)
		++i;
	if (ft_strncmp("export", args[i], 7) == 0 && \
	ft_strncmp("export", args[i - 1], 7) == 0 && i > 0)
		ms_setenv("export", "", var->envp);
	if (args[1] == NULL)
	{
		print_all_env(args, var);
		return (SUCCESS);
	}
	else
	{
		if (is_equal_exist(args[i]))
			ms_setenv(get_first_line(args[i]), get_second_line(args[i]), var->envp);
		else
			ms_setenv(args[i], "", var->envp);
		return (SUCCESS);
	}
	return (FAILURE);
}
