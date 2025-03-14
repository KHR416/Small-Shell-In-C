/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:23:33 by chakim            #+#    #+#             */
/*   Updated: 2025/03/14 15:40:10 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <libft.h>
#include <stdlib.h>

int	ms_exit(char **args, t_msvar *msvar)
{
	size_t	i;
	int		exit_status;

	i = 0;	
	ft_putendl_fd("exit", STDERR_FILENO);
	
	if (args[1] == NULL)
	{
		clear_msvar(msvar);
		exit(msvar->exit_status);
	}
	while (args[1][i] != '\0')
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
			clear_msvar(msvar);
			exit(2);
		}
		i++;
	}
	if (args[2] != NULL)
    {
        ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
        return (FAILURE);
    }
	exit_status = ft_atoi(args[1]);
	clear_msvar(msvar);
	exit(exit_status);
}
