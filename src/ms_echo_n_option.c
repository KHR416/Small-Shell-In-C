/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo_n_option.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:08:43 by chakim            #+#    #+#             */
/*   Updated: 2025/02/21 15:41:59 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
	This fuction does almost same thing with ms_echo,
	but print nothing after print last argument.
*/
int	ms_echo_n_option(char **args)
{
	int	i;

	if (args[1] == NULL)
		return (SUCCESS);
	i = 1;
	while (ft_strncmp("-n", args[i], 3) == 0)
		++i;
	while (args[i + 1] != NULL)
	{
		printf("%s ", args[i]);
		++i;
	}
	printf("%s", args[i]);
	return (SUCCESS);
}
