/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:54:05 by chakim            #+#    #+#             */
/*   Updated: 2025/03/22 16:57:10 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_all_env(t_msvar *var)
{
	char	**env;

	env = var->envp;
	while (*env != NULL)
	{
		print_single_env(*env);
		++env;
	}
}

static void	print_invalid_arg_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("`: not a valid identifier\n", 2);
}

static int	handle_single_arg(char *arg, t_msvar *var)
{
	char	*first_line;
	char	*second_line;

	if (!is_valid_arg(arg))
	{
		print_invalid_arg_error(arg);
		return (0);
	}
	first_line = get_first_line(arg);
	second_line = get_second_line(arg);
	if (!first_line || !second_line)
	{
		free(first_line);
		free(second_line);
		return (0);
	}
	ms_setenv(first_line, second_line, &var->envp, var->buf);
	free(first_line);
	free(second_line);
	return (1);
}

int	ms_export(char **args, t_msvar *var)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
	{
		print_all_env(var);
		return (SUCCESS);
	}
	while (args[i] != NULL)
	{
		if (!handle_single_arg(args[i], var))
		{
			i++;
			continue ;
		}
		i++;
	}
	return (SUCCESS);
}
