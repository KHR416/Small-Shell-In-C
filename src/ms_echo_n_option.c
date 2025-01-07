/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo_n_option.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:08:43 by chakim            #+#    #+#             */
/*   Updated: 2025/01/06 09:03:27 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

/*
	This fuction does almost same thing with ms_echo,
	but print nothing after print last argument.
*/
int	ms_echo_n_option(char **args)
{
	int	i;

	if (args[2] == NULL)
		return (SUCCESS);
	i = 1;
	while (ft_strcmp("-n", args[i]) == 0)
		++i;
	while (args[i + 1] != NULL)
	{
		printf("%s ", args[i]);
		++i;
	}
	printf("%s", args[i]);
	return (SUCCESS);
}
