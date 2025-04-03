/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:54:05 by chakim            #+#    #+#             */
/*   Updated: 2025/03/17 16:42:38 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "minishell.h"
/*
This function prints absolute current directory.
*/
int	ms_pwd(t_msvar *msvar)
{
	char	*cur_dir;

	cur_dir = ms_getcwd(msvar);
	printf("%s\n", cur_dir);
	free(cur_dir);
	return (SUCCESS);
}
