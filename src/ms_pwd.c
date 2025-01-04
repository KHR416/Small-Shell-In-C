/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:54:05 by chakim            #+#    #+#             */
/*   Updated: 2025/01/04 20:43:21 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_args.h"
#include "minishell.h"
/*
This function prints absolute current directory.
*/
void	ms_pwd(void)
{
	char	*cur_dir;

	cur_dir = ms_getcwd();
	printf("%s\n", cur_dir);
	free(cur_dir);
	return (SUCCESS);
}
