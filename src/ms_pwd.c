/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:54:05 by chakim            #+#    #+#             */
/*   Updated: 2025/03/15 23:35:42 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
/*
This function prints absolute current directory.
*/
int	ms_pwd(t_buf *buf)
{
	char	*cur_dir;

	cur_dir = ms_getcwd(buf);
	printf("%s\n", cur_dir);
	free(cur_dir);
	return (SUCCESS);
}
