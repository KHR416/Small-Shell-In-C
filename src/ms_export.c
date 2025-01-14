/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:54:05 by chakim            #+#    #+#             */
/*   Updated: 2025/01/14 18:36:42 by chakim           ###   ########.fr       */
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
	char	*checker;
	int		i;

	checker = "export";
	if (args[1] == NULL)
	{
		print_all_env(args, var);
		return (SUCCESS);
	}
	else if (ft_strcmp(args[0], args[1]) == 0 && args[2] == NULL)
	{
		ms_setenv();
	}
	else
	{
		i = 0;
		while (ft_strcmp(checker, args[i]) == 0)
			++i;
		if (is_equal_exist(args[i]))
		{

		}
		else
		{
			
		}
	}
}
