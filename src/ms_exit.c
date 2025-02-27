/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:23:33 by chakim            #+#    #+#             */
/*   Updated: 2025/02/27 06:48:34 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <libft.h>
#include <stdlib.h>

int	ms_exit(char **args, t_msvar *msvar)
{
	size_t	i = 0;
	
	ft_putendl_fd("exit", STDERR_FILENO);
	while (args[i])
		++i;
	if (i > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (FAILURE);
	}
	if (i == 1)
	{
		clear_msvar(msvar);
		exit(msvar->exit_status);
	}
	if (i == 2)
	{
		for (size_t i = 0; i < ft_strlen(args[1]); ++i)
			if (!ft_isdigit(args[1][i]))
			{
				ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
				clear_msvar(msvar);
				exit(2);
			}
		int	exit_status = ft_atoi(args[1]);
		clear_msvar(msvar);
		exit(exit_status);
	}
	return (FAILURE);
}
