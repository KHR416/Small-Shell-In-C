/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:54:49 by chakim            #+#    #+#             */
/*   Updated: 2025/03/22 16:48:05 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_error_checker(char **args)
{
	char	*path;

	path = args[1];
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (FAILURE);
	}
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (127);
	}
	if (access(path, R_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (126);
	}
	return (SUCCESS);
}
