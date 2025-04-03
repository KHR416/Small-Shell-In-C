/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:23:33 by chakim            #+#    #+#             */
/*   Updated: 2025/03/22 16:49:34 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <libft.h>
#include <stdlib.h>

static void	print_exit_message(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
}

static int	handle_non_numeric_exit(t_msvar *msvar)
{
	ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
	clear_msvar(msvar);
	exit(2);
}

static int	handle_too_many_args(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (FAILURE);
}

static void	exit_with_status(t_msvar *msvar, int exit_status)
{
	clear_msvar(msvar);
	exit(exit_status);
}

int	ms_exit(char **args, t_msvar *msvar)
{
	int		exit_status;
	size_t	i;

	print_exit_message();
	if (args[1] == NULL)
		exit_with_status(msvar, msvar->exit_status);
	i = 0;
	while (args[1][i] != '\0')
	{
		if (!ft_isdigit(args[1][i]))
			return (handle_non_numeric_exit(msvar));
		i++;
	}
	if (args[2] != NULL)
		return (handle_too_many_args());
	exit_status = ft_atoi(args[1]);
	exit_with_status(msvar, exit_status);
	return (SUCCESS);
}
